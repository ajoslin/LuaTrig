#include "LuaUtil.h"
#include "LuaTrig.h"
#include <lua.hpp>

 
Trigger *LuaUtil::getudata_trigger(lua_State *L, int index=1)
{
	void *userdata = luaL_checkudata(L, index, TRIGGER_METATABLE);
	luaL_argcheck(L, userdata!=NULL, index, "'Trigger' expected");
	int * trigid = (int *)userdata;
	
	return LuaTrig::instance()->get_trigger(*trigid);
}

Condition *LuaUtil::getudata_condition(lua_State *L, int index)
{
	void *userdata = luaL_checkudata(L, index, CONDITION_METATABLE);
	luaL_argcheck(L, userdata!=NULL, index, "'Condition' expected");

	LuaEC *luacond = (LuaEC *)userdata;

	Trigger *trigger = LuaTrig::instance()->get_trigger(luacond->triggerid);

	list<Condition *>::iterator it = trigger->conds.begin();
	for (int i=0; i<luacond->id; i++) it++;

	return *it;

}

Effect *LuaUtil::getudata_effect(lua_State *L, int index)
{
	void *userdata = luaL_checkudata(L, index, CONDITION_METATABLE);
	luaL_argcheck(L, userdata!=NULL, index, "'Effect' expected");
	
	LuaEC *luaeffect = (LuaEC *)userdata;

	Trigger *trigger = LuaTrig::instance()->get_trigger(luaeffect->triggerid);

	list<Effect *>::iterator it = trigger->effects.begin();
	for (int i=0; i<luaeffect->id; i++) it++;

	return *it;

}