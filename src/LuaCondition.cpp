#include "LuaCondition.h"
#include "LuaUtil.h"

//EC_CREATOR in LuaUtil
EC_CREATOR(LuaCondition::f_None, CONDITION_None);
EC_CREATOR(LuaCondition::f_BringObjectToArea, CONDITION_BringObjectToArea);
EC_CREATOR(LuaCondition::f_BringObjectToObject, CONDITION_BringObjectToObject);
EC_CREATOR(LuaCondition::f_OwnObjects, CONDITION_OwnObjects);
EC_CREATOR(LuaCondition::f_OwnFewerObjects, CONDITION_OwnFewerObjects);
EC_CREATOR(LuaCondition::f_ObjectsInArea, CONDITION_ObjectsInArea);
EC_CREATOR(LuaCondition::f_DestroyObject, CONDITION_DestroyObject);
EC_CREATOR(LuaCondition::f_CaptureObject, CONDITION_CaptureObject);
EC_CREATOR(LuaCondition::f_AccumulateAttribute, CONDITION_AccumulateAttribute);
EC_CREATOR(LuaCondition::f_ResearchTechnology, CONDITION_ResearchTechnology);
EC_CREATOR(LuaCondition::f_Timer, CONDITION_Timer);
EC_CREATOR(LuaCondition::f_ObjectSelected, CONDITION_ObjectSelected);
EC_CREATOR(LuaCondition::f_AISignal, CONDITION_AISignal);
EC_CREATOR(LuaCondition::f_PlayerDefeated, CONDITION_PlayerDefeated);
EC_CREATOR(LuaCondition::f_ObjectHasTarget, CONDITION_ObjectHasTarget);
EC_CREATOR(LuaCondition::f_ObjectVisible, CONDITION_ObjectVisible);
EC_CREATOR(LuaCondition::f_ObjectNotVisible, CONDITION_ObjectNotVisible);
EC_CREATOR(LuaCondition::f_ResearchingTechnology, CONDITION_ResearchingTechnology);
EC_CREATOR(LuaCondition::f_UnitsGarrisoned, CONDITION_UnitsGarrisoned);
EC_CREATOR(LuaCondition::f_DifficultyLevel, CONDITION_DifficultyLevel);

//Timer condition uses amount method in lua
int LuaCondition::m_setAmount(lua_State *L)
{
	Condition *cond = LuaUtil::getudata_condition(L, 1);
	if (!cond->valid_property(CONDITIONP_Amount))
		return luaL_error(L, "Error in amount()! Condition %s cannot have an amount.", Condition::types[cond->type]);

	int amount=luaL_checknumber(L, 2);
	if (amount<0)
		return luaL_error(L, "Error in amount()! Expected a valid amount, got %d.", amount);

	
	if (cond->type==CONDITION_Timer)
		cond->timer=amount;
	else
		cond->amount=amount;

	return 0;
}

int LuaCondition::m_setResourceType(lua_State *L)
{
	Condition *cond = LuaUtil::getudata_condition(L, 1);
	if (!cond->valid_property(CONDITIONP_ResourceType))
		return luaL_error(L, "Error in resource()! Condition %s cannot have a resource.", Condition::types[cond->type]);
	
	int id;
	if (lua_isnumber(L, 2))
	{
		id = luaL_checknumber(L, 2);
		if (!my_util::is_res_id(id))
			return luaL_error(L, "Error in resource()! Expected resource name or id, got %d.", id);
	}
	else if (lua_isstring(L, 2))
	{
		char *resname=(char *)lua_tostring(L, 2);
		id = my_util::get_res_id(resname);
		if (id==-1)
			return luaL_error(L, "Error in resource()! Expected resource name or id, got %s.", resname);
	} 
	else
		return luaL_error(L, "Error in resource()! Expected resource name or id.");

	cond->resource_type=id;

	return 0;
}

int LuaCondition::m_setUIDObject(lua_State *L)
{
	Condition *cond = LuaUtil::getudata_condition(L, 1);
	if (!cond->valid_property(CONDITIONP_UIDObject))
		return luaL_error(L, "Error in unit_object()! Condition %s cannot have a unit object.", Condition::types[cond->type]);
	
	int uid = luaL_checknumber(L, 2);
	if (uid<=0) //TODO Add Scenario check for unit id
		return luaL_error(L, "Error in unit_object()! Expected valid unit ID, got %d.", uid);
	
	cond->uid_object=uid;

	return 0;
}

int LuaCondition::m_setUIDLocation(lua_State *L)
{
	Condition *cond=LuaUtil::getudata_condition(L, 1);
	if (!cond->valid_property(CONDITIONP_UIDLocation))
		return luaL_error(L, "Error in unit_location()! Condition %s cannot have a unit location.", Condition::types[cond->type]);
	
	int uid = luaL_checknumber(L, 2);
	if (uid<=0) //TODO Add Scenario check for unit id
		return luaL_error(L, "Error in unit_location()! Expected valid unit ID, got %d.", uid);
	
	cond->uid_location=uid;

	return 0;
}

int LuaCondition::m_setPlayer(lua_State *L)
{
	Condition *cond=LuaUtil::getudata_condition(L, 1);
	if (!cond->valid_property(CONDITIONP_Player))
		return luaL_error(L, "Error in player()! Condition %s cannot have a player.", Condition::types[cond->type]);
	
	int player = luaL_checknumber(L, 2);
	if (player<0 || player>8)
		return luaL_error(L, "Error in player()! Expected valid player, got %d", player);

	cond->player=player;

	return 0;
}

int LuaCondition::m_setTechnology(lua_State *L)
{
	Condition *cond=LuaUtil::getudata_condition(L, 1);
	if (!cond->valid_property(CONDITIONP_Technology))
		return luaL_error(L, "Error in technology()! Condition %s cannot have a technology.", Condition::types[cond->type]);
	
	int tech = luaL_checknumber(L, 2);
	if (tech<0)
		return luaL_error(L, "Error in technology()! Expected valid technology, got %d");

	cond->technology=tech;

	return 0;
}

int LuaCondition::m_setArea(lua_State *L)
{
	Condition *cond=LuaUtil::getudata_condition(L, 1);
	if (!cond->valid_property(CONDITIONP_Area))
		return luaL_error(L, "Error in area()! Condition %s cannot have an area.", Condition::types[cond->type]);
	
	lua_getnonnegative(x1, 2, "area()");
	lua_getnonnegative(y1, 3, "area()");
	lua_getnonnegative(x2, 4, "area()");
	lua_getnonnegative(y2, 5, "area()");
	if (x1>x2 && y1>y2)
		return luaL_error(L, "Error in area()! Expected location (x1,y1) to be less than location (x2,y2), got (x1,y1)=(%d,%d) and (x2,y2)=(%d,%d)", x1, y1, x2, y2);
	
	cond->area.ll.x=x1;
	cond->area.ll.y=y1;
	cond->area.ur.x=x2;
	cond->area.ur.y=y2;

	return 0;
}

int LuaCondition::m_setUnitType(lua_State *L)
{
	Condition *cond = LuaUtil::getudata_condition(L, 1);
	if (!cond->valid_property(CONDITIONP_UnitType))
		return luaL_error(L, "Error in unit_type()! Condition %s cannot have a unit type.", Condition::types[cond->type]);

	//Supports string spellings
	int id;
	if (lua_isnumber(L, 2)) 
	{
		id = luaL_checknumber(L, 2);
		if (!my_util::is_utype(id))
			return luaL_error(L, "Error in unit_type()! Expected unit type name or id, got %d.", id);
	}
	else if (lua_isstring(L, 2))
	{
		char *type=(char *)lua_tostring(L, 2);
		id = my_util::get_utype(type);
		if (id==-2)
			return luaL_error(L, "Error in unit_type()! Expected unit type name or id, got %s.", type);
	}
	else
		return luaL_error(L, "Error in unit_type()! Expected unit type name or id.");

	cond->unit_type=id;

	return 0;
}

int LuaCondition::m_setUnitConst(lua_State *L)
{
	Condition *cond=LuaUtil::getudata_condition(L, 1);
	if (!cond->valid_property(CONDITIONP_UnitConst))
		return luaL_error(L, "Error in unit_const()! Condition %s cannot have a unit constant.", Condition::types[cond->type]);
	
	int uid = luaL_checknumber(L, 2);
	if (uid<=0)
		return luaL_error(L, "Error in unit_const()! Expected valid unit ID, got %d.", uid);
	
	cond->unit_const=uid;

	return 0;
}

int LuaCondition::m_setUnitGroup(lua_State *L)
{
	Condition *condition = LuaUtil::getudata_condition(L, 1);
	if(!condition->valid_property(CONDITIONP_UnitGroup))
		return luaL_error(L, "Error in unit_group()! Condition %s cannot have a unit group.", condition->types[condition->type]);
	
	int grp;
	if (lua_isstring(L, 2))
	{
		char *group=(char *)lua_tostring(L, 2);
		grp = my_util::get_ugroup(group);
		if (grp==-1)
			return luaL_error(L, "Error in unit_group()! Expected unit group name, got %s.", grp);
	}
	else
		return luaL_error(L, "Error in unit_group()! Expected unit group name.");

	condition->unit_group=grp;
	return 0;
}

int LuaCondition::m_setAISignal(lua_State *L)
{
	Condition *cond=LuaUtil::getudata_condition(L, 1);
	if (!cond->valid_property(CONDITIONP_AISignal))
		return luaL_error(L, "Error in ai_signal()! Condition %s cannot have an ai_signal.", Condition::types[cond->type]);
	
	int sign = luaL_checknumber(L, 2);
	if (sign<0) //TODO Add Scenario check for unit id
		return luaL_error(L, "Error in ai_signal()! Expected valid AI signal, got %d.", sign);
	
	cond->ai_signal=sign;

	return 0;
}



/** References all the functions (static, like Condition.ObjectsInArea()) for conditions */
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

/** References all the methods (object-methods, non-static) for conditions */
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