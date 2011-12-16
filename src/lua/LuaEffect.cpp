/** References all the functions (static, like Condition.ObjectsInArea()) for effects 
const struct luaL_reg effect_funcs[] = {
	{"None", LuaEffect::f_None},
	{"ChangeDiplomacy", LuaEffect::f_ChangeDiplomacy},
	{"ResearchTechnology", LuaEffect::f_ResearchTechnology},
	{"SendChat", LuaEffect::f_SendChat},
	{"PlaySound", LuaEffect::f_PlaySound},
	{"SendTribute", LuaEffect::f_SendTribute},
	{"UnlockGate", LuaEffect::f_UnlockGate},
	{"LockGate", LuaEffect::f_LockGate},
	{"ActivateTrigger", LuaEffect::f_ActivateTrigger},
	{"DeactivateTrigger", LuaEffect::f_DeactivateTrigger},
	{"AIScriptGoal", LuaEffect::f_AIScriptGoal},
	{"CreateObject", LuaEffect::f_CreateObject},
	{"TaskObject", LuaEffect::f_TaskObject},
	{"DeclareVictory", LuaEffect::f_DeclareVictory},
	{"KillObject", LuaEffect::f_KillObject},
	{"RemoveObject", LuaEffect::f_RemoveObject},
	{"ChangeView", LuaEffect::f_ChangeView},
	{"Unload", LuaEffect::f_Unload},
	{"ChangeOwnership", LuaEffect::f_ChangeOwnership},
	{"Patrol", LuaEffect::f_Patrol},
	{"DisplayInstructions", LuaEffect::f_DisplayInstructions},
	{"ClearInstructions", LuaEffect::f_ClearInstructions},
	{"FreezeUnit", LuaEffect::f_FreezeUnit},
	{"UseAdvancedButtons", LuaEffect::f_UseAdvancedButtons},
	{"DamageObject", LuaEffect::f_DamageObject},
	{"PlaceFoundation", LuaEffect::f_PlaceFoundation},
	{"ChangeObjectName", LuaEffect::f_ChangeObjectName},
	{"ChangeObjectHP", LuaEffect::f_ChangeObjectHP},
	{"ChangeObjectAttack", LuaEffect::f_ChangeObjectAttack},
	{"StopUnit", LuaEffect::f_StopUnit},
	{NULL, NULL},
};

/** References all the methods (object-methods, non-static) for effects 
const struct luaL_reg effect_methods[] = {
	{"amount", LuaEffect::m_setAmount},
	{"location", LuaEffect::m_setLocation},
	{"area", LuaEffect::m_setArea},
	{"ai_goal", LuaEffect::m_setAIGoal},
	{"diplomacy", LuaEffect::m_setDiplomacy},
	{"time", LuaEffect::m_setDisplayTime},
	{"panel", LuaEffect::m_setPanel},
	{"player", LuaEffect::m_setPlayerSource},
	{"player_target", LuaEffect::m_setPlayerTarget},
	{"resource", LuaEffect::m_setResource},
	{"technology", LuaEffect::m_setTechnology},
	{"trigger", LuaEffect::m_setTriggerIndex},
	{"units", LuaEffect::m_setUIDs},
	{"unit_location", LuaEffect::m_setUIDLocation},
	{"unit_type", LuaEffect::m_setUnitType},
	{"unit_const", LuaEffect::m_setUnitConst},
	{"unit_group", LuaEffect::m_setUnitGroup},
	{"sound", LuaEffect::m_setSound},
	{"text", LuaEffect::m_setText},
	{NULL, NULL}
};
	
void LuaEffect::lua_init(lua_State *L)
{
	luaL_newmetatable(L, EFFECT_METATABLE); //leaves new metatable on the stack

	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);

	luaL_openlib(L, NULL, effect_methods, 0); // register functions in the metatable
	luaL_openlib(L, "Effect", effect_funcs, 0); //register "Effect.*" functions globally
}*/