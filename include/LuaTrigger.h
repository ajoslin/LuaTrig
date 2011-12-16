
#ifndef LUA_TRIGGER_H
#define LUA_TRIGGER_H

#include "LuaTrig.h"

class lua_State; //fwd declaration here so we don't have to include lua

class LuaTrigger
{
public:
	/** f = function, lua static function */
	static int f_new(lua_State *L);

	/** m = method, lua object method */
	static int m_setName(lua_State *L);
	static int m_setDescription(lua_State *L);
	static int m_setOn(lua_State *L);
	static int m_setLoop(lua_State *L);
	static int m_setObjective(lua_State *L);
	static int m_setDescOrder(lua_State *L);
	static int m_addCondition(lua_State *L);
	static int m_addEffect(lua_State *L);

	/** Registers trigger lib to lua for usage in lua */
	static void lua_init(lua_State *L);
};

#endif