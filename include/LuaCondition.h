#ifndef LUA_CONDITION_H
#define LUA_CONDITION_H

#include "Condition.h"
#include <lua.hpp>

class LuaCondition
{
public:
	/** f = function, lua static function */
	static int f_None(lua_State *L);
	static int f_BringObjectToArea(lua_State *L);
	static int f_BringObjectToObject(lua_State *L);
	static int f_OwnObjects(lua_State *L);
	static int f_OwnFewerObjects(lua_State *L);
	static int f_ObjectsInArea(lua_State *L);
	static int f_DestroyObject(lua_State *L);
	static int f_CaptureObject(lua_State *L);
	static int f_AccumulateAttribute(lua_State *L);
	static int f_ResearchTechnology(lua_State *L);
	static int f_Timer(lua_State *L);
	static int f_ObjectSelected(lua_State *L);
	static int f_AISignal(lua_State *L);
	static int f_PlayerDefeated(lua_State *L);
	static int f_ObjectHasTarget(lua_State *L);
	static int f_ObjectVisible(lua_State *L);
	static int f_ObjectNotVisible(lua_State *L);
	static int f_ResearchingTechnology(lua_State *L);
	static int f_UnitsGarrisoned(lua_State *L);
	static int f_DifficultyLevel(lua_State *L);

	/** m = method, lua object method */
	static int m_setAmount(lua_State *L);
	static int m_setResourceType(lua_State *L);
	static int m_setUIDObject(lua_State *L);
	static int m_setUIDLocation(lua_State *L);
	static int m_setPlayer(lua_State *L);
	static int m_setTechnology(lua_State *L);
	static int m_setTimer(lua_State *L);
	static int m_setArea(lua_State *L);
	static int m_setUnitType(lua_State *L);
	static int m_setUnitConst(lua_State *L);
	static int m_setUnitGroup(lua_State *L);
	static int m_setAISignal(lua_State *L);

	/** Registers condition lib to lua for usage in lua */
	static void lua_init(lua_State *L);	
};

#endif