#ifndef LUA_UTIL_H
#define LUA_UTIL_H

#include "Trigger.h"

class lua_State; //just forward it here so we don't have to include lua.hpp

#define TRIGGER_METATABLE "LuaBook.trigger"
#define EFFECT_METATABLE "LuaBook.trigger_effect"
#define CONDITION_METATABLE "LuaBook.trigger_condition"

/**
 * Creates a function for lua which returns type of given effect/condition
 * Lua effect/cond creation just return the type of eff/cond,
 * which is then passed to trigger:condition() or trigger:effect()
 */ 
#define EC_CREATOR(func, type) \
int func (lua_State *L) \
{ \
	lua_pushnumber(L, type); \
	return 1; \
}

//Each condition/effect stores one of these structs in lua userdata. then C retrieves this to know what cond/effect is being called
struct LuaEC
{
	int triggerid;
	int id;
	LuaEC(int ti, int i)
	: triggerid(ti), id(i)
	{
	}
};

//Gets positive number or error
#define lua_getnonnegative(varname, index, name) int varname = luaL_checknumber(L, index); \
	if (varname<0) return luaL_error(L, "Error in %s! Expected postiive number, got %d.", name, varname);

//Gets number != -1 or error
#define lua_getnonneg1(varname, index, name) int varname = luaL_checknumber(L, index); \
	if (varname==-1) return luaL_error(L, "Error in %s! Expected number not equal to -1, got -1.", name);

#define lua_getpositive(varname, index, name) int varname = luaL_checknumber(L, index); \
	if (varname<=0) return luaL_error(L, "Error in %s! Expected nonnegative number, got %d.", name, varname);


class LuaUtil
{
public:
	/** Gets various userdata from a certain index on lua stack */
	/** Is stored here because these are used multiple lua classes */
	static Trigger *getudata_trigger(lua_State *L, int index);
	static Effect *getudata_effect(lua_State *L, int index);
	static Condition *getudata_condition(lua_State *L, int index);
};

#endif