/** References all the methods (object-methods, non-static) for triggers 
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

/** References all the functions (static, like Trigger.new) for triggers 
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
}*/