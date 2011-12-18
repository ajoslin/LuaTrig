#include "LuaTrig.h"
#include "LuaTrigger.h"
#include "Trigger.h"
#include "../util/luautil.h"
#include <lua.hpp>
#include <string.h>
#include <stdio.h>

/**
 * Create a new trigger, push it onto lua stack, and put it in C++ array
 */
int LuaTrigger::f_new(lua_State *L)
{
	int id = luaL_checknumber(L, 1);
	if (id<0)
		return luaL_error(L, "Error in Trigger()! Expected id>=0, got id=%d", id);
	else if (id>=MAX_TRIGGERS) 
	 	return luaL_error(L, "Error in Trigger()! Expected id less than %d, got %d", MAX_TRIGGERS, id);
	else if (LuaTrig::instance()->triggers.size()>id) 
	 	return luaL_error(L, "Error in Trigger()! Trigger with id %d already exists!", id);
	else if (LuaTrig::instance()->triggers.size()<id) 
		return luaL_error(L, "Error in Trigger()! Cannot create trigger with id %d because trigger with previous id %d does not exist.", id, id-1);
	
	//stores this trigger's index in lua, so it can be retrieved any time
	int * trig_index = (int *)lua_newuserdata(L, sizeof(int));
	*trig_index = LuaTrig::instance()->triggers.size();

	luaL_getmetatable(L, TRIGGER_METATABLE);
	lua_setmetatable(L, -2);

	Trigger *t = new Trigger(*trig_index);
	LuaTrig::instance()->triggers.push_back(t);

	return 1; /* new userdata is already on the stack */
}

int LuaTrigger::m_setName(lua_State *L)
{
	Trigger *trig = getudata_trigger(L, 1);

	const char *name = luaL_checkstring(L, 2);
	if (strlen(name)>Trigger::MAX_TRIGNAME)
		return luaL_error(L, "Error in trigger:name()! Trigger name is too long (got length %d, expected <%d", strlen(name), Trigger::MAX_TRIGNAME);
	
	trig->name.resize(strlen(name));
	trig->name.assign(name);

	return 0;
}

int LuaTrigger::m_setDescription(lua_State *L)
{
	Trigger *trig = getudata_trigger(L, 1);

	const char *descr = luaL_checkstring(L, 2);
	
	trig->description.resize(strlen(descr));
	trig->description.assign(descr);

	return 0;
}
int LuaTrigger::m_setOn(lua_State *L)
{
	Trigger * trig = getudata_trigger(L, 1);
	if (!lua_isboolean(L, 2))
		return luaL_error(L, "Error in trigger:on()! Expected boolean");
	int on=lua_toboolean(L, 2);

	trig->state=on;
	return 0;
}

int LuaTrigger::m_setLoop(lua_State *L)
{
	Trigger * trig = getudata_trigger(L, 1);
	if (!lua_isboolean(L, 2))
		return luaL_error(L, "Error in trigger:loop()! Expected boolean");
	int loop=lua_toboolean(L, 2);
	trig->loop=loop;
	return 0;
}

int LuaTrigger::m_setObjective(lua_State *L)
{
	Trigger * trig = getudata_trigger(L, 1);
	if (!lua_isboolean(L, 2))
		return luaL_error(L, "Error in trigger:objective()! Expected boolean");
	int obj=lua_toboolean(L, 2);
	trig->obj=(char)obj;
	return 0;
}

int LuaTrigger::m_setDescOrder(lua_State *L)
{
	Trigger * trig = getudata_trigger(L, 1);
	int order = luaL_checknumber(L, 2);
	trig->obj_order=order;
	return 0;
}

int LuaTrigger::m_addEffect(lua_State *L)
{
	Trigger *trig = getudata_trigger(L, 1);
	if (!lua_isnumber(L,2))
		return luaL_error(L, "Error in trigger:effect()! Expected valid effect type.");
	int effectType = luaL_checknumber(L, 2);
	if (effectType>NUM_EFFECTS || effectType<0)
		return luaL_error(L, "Error in trigger:effect()! Expected valid effect type from 0-%d, got %d", MAX_EFFECT, effectType);
	
	//store this effect's id and it's parent trigger id in lua
	LuaEC *udata = (LuaEC *)lua_newuserdata(L, sizeof(LuaEC));
	udata->triggerid = trig->index;
	udata->id = trig->effects.size();

	luaL_getmetatable(L, EFFECT_METATABLE);
	lua_setmetatable(L, -2);

	//add a new effect to trigger's list and set effect's type
	Effect *effect = new Effect();
	effect->type=effectType;

	trig->effects.push_back(effect);

	//return the effect
	return 1;
}

int LuaTrigger::m_addCondition(lua_State *L)
{
	Trigger *trig = getudata_trigger(L, 1);
	if (!lua_isnumber(L,2))
		return luaL_error(L, "Error in trigger:condition()! Expected valid condition type");
	int condType = luaL_checknumber(L, 2);
	if (condType>NUM_CONDS || condType<0)
		return luaL_error(L, "Error in trigger:condition()! Invalid condition type given");

	//store this condition's id and it's parent trigger id in lua
	LuaEC *udata = (LuaEC *)lua_newuserdata(L, sizeof(LuaEC));
	udata->triggerid = trig->index;
	udata->id = trig->conds.size();

	luaL_getmetatable(L, CONDITION_METATABLE);
	lua_setmetatable(L, -2);

	//add condition to trigger's list and set condition's type
	Condition *cond = new Condition();
	cond->type=condType;
	trig->conds.push_back(cond);

	//return the cond
	return 1;
}

/** References all the methods (object-methods, non-static) for triggers */
const struct luaL_reg trigger_methods[] = {
	{"name", LuaTrigger::m_setName},
	{"description", LuaTrigger::m_setDescription},
	{"on", LuaTrigger::m_setOn},
	{"loop", LuaTrigger::m_setLoop},
	{"objective", LuaTrigger::m_setObjective},
	{"desc_order", LuaTrigger::m_setDescOrder},
	{"effect", LuaTrigger::m_addEffect},
	{"condition", LuaTrigger::m_addCondition},
	{NULL, NULL}
};

/** References all the functions (static, like Trigger.new) for triggers */
const struct luaL_reg trigger_funcs[] = {
	{NULL, NULL},
};

void LuaTrigger::lua_init(lua_State *L)
{
	luaL_newmetatable(L, TRIGGER_METATABLE); //leaves new metatable on the stack

	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);

	luaL_openlib(L, NULL, trigger_methods, 0); // register functions in the metatable
	luaL_openlib(L, "Trigger", trigger_funcs, 0); //register "Trigger.*" functions globally

	lua_pushcfunction(L, LuaTrigger::f_new);
	lua_setglobal(L, "Trigger");
}

