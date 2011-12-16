#ifndef LUA_EFFECT_H
#define LUA_EFFECT_H

#include "Effect.h"

class lua_State; //fwd declaration here so we don't have to include lua

class LuaEffect
{
public:
	/** f = function, lua static function */
	static int f_None(lua_State *L);
	static int f_ChangeDiplomacy(lua_State *L);
	static int f_ResearchTechnology(lua_State *L);
	static int f_SendChat(lua_State *L);
	static int f_PlaySound(lua_State *L);
	static int f_SendTribute(lua_State *L);
	static int f_UnlockGate(lua_State *L);
	static int f_LockGate(lua_State *L);
	static int f_ActivateTrigger(lua_State *L);
	static int f_DeactivateTrigger(lua_State *L);
	static int f_AIScriptGoal(lua_State *L);
	static int f_CreateObject(lua_State *L);
	static int f_TaskObject(lua_State *L);
	static int f_DeclareVictory(lua_State *L);
	static int f_KillObject(lua_State *L);
	static int f_RemoveObject(lua_State *L);
	static int f_ChangeView(lua_State *L);
	static int f_Unload(lua_State *L);
	static int f_ChangeOwnership(lua_State *L);
	static int f_Patrol(lua_State *L);
	static int f_DisplayInstructions(lua_State *L);
	static int f_ClearInstructions(lua_State *L);
	static int f_FreezeUnit(lua_State *L);
	static int f_UseAdvancedButtons(lua_State *L);
	static int f_DamageObject(lua_State *L);
	static int f_PlaceFoundation(lua_State *L);
	static int f_ChangeObjectName(lua_State *L);
	static int f_ChangeObjectHP(lua_State *L);
	static int f_ChangeObjectAttack(lua_State *L);
	static int f_StopUnit(lua_State *L);

	/** m = method, lua object method */
	static int m_setAmount(lua_State *L);
	static int m_setLocation(lua_State *L);
	static int m_setArea(lua_State *L);
	static int m_setAIGoal(lua_State *L);
	static int m_setDiplomacy(lua_State *L);
	static int m_setDisplayTime(lua_State *L);
	static int m_setPanel(lua_State *L);
	static int m_setPlayerSource(lua_State *L);
	static int m_setPlayerTarget(lua_State *L);
	static int m_setResource(lua_State *L);
	static int m_setTechnology(lua_State *L);
	static int m_setTriggerIndex(lua_State *L);
	static int m_setUIDs(lua_State *L);
	static int m_setUIDLocation(lua_State *L);
	static int m_setUnitType(lua_State *L);
	static int m_setUnitConst(lua_State *L);
	static int m_setUnitGroup(lua_State *L);
	static int m_setSound(lua_State *L);
	static int m_setText(lua_State *L);

	/** Registers effect lib to lua for usage in lua */
	static void lua_init(lua_State *L);	
};

#endif