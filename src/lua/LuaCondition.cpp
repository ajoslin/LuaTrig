
/** References all the functions (static, like Condition.ObjectsInArea()) for conditions 
const struct luaL_reg cond_funcs[] = {
	{"None", LuaCondition::f_None},
	{"BringObjectToArea", LuaCondition::f_BringObjectToArea},
	{"BringObjectToObject", LuaCondition::f_BringObjectToObject},
	{"OwnObjects", LuaCondition::f_OwnObjects},
	{"OwnFewerObjects", LuaCondition::f_OwnFewerObjects},
	{"ObjectsInArea", LuaCondition::f_ObjectsInArea},
	{"DestroyObject", LuaCondition::f_DestroyObject},
	{"CaptureObject", LuaCondition::f_CaptureObject},
	{"AccumulateAttribute", LuaCondition::f_AccumulateAttribute},
	{"ResearchTechnology", LuaCondition::f_ResearchTechnology},
	{"Timer", LuaCondition::f_Timer},
	{"ObjectSelected", LuaCondition::f_ObjectSelected},
	{"AISignal", LuaCondition::f_AISignal},
	{"PlayerDefeated", LuaCondition::f_PlayerDefeated},
	{"ObjectHasTarget", LuaCondition::f_ObjectHasTarget},
	{"ObjectVisible", LuaCondition::f_ObjectVisible},
	{"ObjectNotVisible", LuaCondition::f_ObjectNotVisible},
	{"ResearchingTechnology", LuaCondition::f_ResearchingTechnology},
	{"UnitsGarrisoned", LuaCondition::f_UnitsGarrisoned},
	{"DifficultyLevel", LuaCondition::f_DifficultyLevel},
	{NULL, NULL},
};

/** References all the methods (object-methods, non-static) for conditions 
const struct luaL_reg cond_methods[] = {
	{"amount", LuaCondition::m_setAmount},
	{"resource", LuaCondition::m_setResourceType},
	{"unit_object", LuaCondition::m_setUIDObject},
	{"unit_location", LuaCondition::m_setUIDLocation},
	{"player", LuaCondition::m_setPlayer},
	{"technology", LuaCondition::m_setTechnology},
	//no need to have timer function, Timer condition will use the amount field
	{"area", LuaCondition::m_setArea},
	{"unit_type", LuaCondition::m_setUnitType},
	{"unit_const", LuaCondition::m_setUnitConst},
	{"unit_group", LuaCondition::m_setUnitGroup},
	{"ai_signal", LuaCondition::m_setAISignal},
	{NULL, NULL}
};
	
void LuaCondition::lua_init(lua_State *L)
{
	luaL_newmetatable(L, CONDITION_METATABLE); //leaves new metatable on the stack

	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);

	luaL_openlib(L, NULL, cond_methods, 0); // register functions in the metatable
	luaL_openlib(L, "Condition", cond_funcs, 0);  //register "Condition.*" functions globally
}
*/