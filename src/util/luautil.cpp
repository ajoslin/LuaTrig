#include "../util/luautil.h"
#include "../lua/LuaFile.h"
#include <lua.hpp>

 
Trigger *getudata_trigger(lua_State *L, int index=1)
{
	void *userdata = luaL_checkudata(L, index, TRIGGER_METATABLE);
	luaL_argcheck(L, userdata!=NULL, index, "'Trigger' expected");
	int * trigid = (int *)userdata;
	
	return LuaFile::current()->triggers.at(*trigid);
}

Condition *getudata_condition(lua_State *L, int index)
{
	void *userdata = luaL_checkudata(L, index, CONDITION_METATABLE);
	luaL_argcheck(L, userdata!=NULL, index, "'Condition' expected");

	LuaEC *luacond = (LuaEC *)userdata;

	Trigger *trigger = LuaFile::current()->triggers.at(luacond->triggerid);

	list<Condition *>::iterator it = trigger->conds.begin();
	for (int i=0; i<luacond->id; i++) it++;

	return *it;

}

Effect *getudata_effect(lua_State *L, int index)
{
	void *userdata = luaL_checkudata(L, index, CONDITION_METATABLE);
	luaL_argcheck(L, userdata!=NULL, index, "'Effect' expected");
	
	LuaEC *luaeffect = (LuaEC *)userdata;

	Trigger *trigger = LuaFile::current()->triggers.at(luaeffect->triggerid);

	list<Effect *>::iterator it = trigger->effects.begin();
	for (int i=0; i<luaeffect->id; i++) it++;

	return *it;

}