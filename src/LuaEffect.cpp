#include "LuaEffect.h"
#include "LuaUtil.h"

//EC_CREATOR defined in LuaUtil
EC_CREATOR(LuaEffect::f_None, EFFECT_None);
EC_CREATOR(LuaEffect::f_ChangeDiplomacy, EFFECT_ChangeDiplomacy);
EC_CREATOR(LuaEffect::f_ResearchTechnology, EFFECT_ResearchTechnology);
EC_CREATOR(LuaEffect::f_SendChat, EFFECT_SendChat);
EC_CREATOR(LuaEffect::f_PlaySound, EFFECT_PlaySound);
EC_CREATOR(LuaEffect::f_SendTribute, EFFECT_SendTribute);
EC_CREATOR(LuaEffect::f_UnlockGate, EFFECT_UnlockGate);
EC_CREATOR(LuaEffect::f_LockGate, EFFECT_LockGate);
EC_CREATOR(LuaEffect::f_ActivateTrigger, EFFECT_ActivateTrigger);
EC_CREATOR(LuaEffect::f_DeactivateTrigger, EFFECT_DeactivateTrigger);
EC_CREATOR(LuaEffect::f_AIScriptGoal, EFFECT_AIScriptGoal);
EC_CREATOR(LuaEffect::f_CreateObject, EFFECT_CreateObject);
EC_CREATOR(LuaEffect::f_TaskObject, EFFECT_TaskObject);
EC_CREATOR(LuaEffect::f_DeclareVictory, EFFECT_DeclareVictory);
EC_CREATOR(LuaEffect::f_KillObject, EFFECT_KillObject);
EC_CREATOR(LuaEffect::f_RemoveObject, EFFECT_RemoveObject);
EC_CREATOR(LuaEffect::f_ChangeView, EFFECT_ChangeView);
EC_CREATOR(LuaEffect::f_Unload, EFFECT_Unload);
EC_CREATOR(LuaEffect::f_ChangeOwnership, EFFECT_ChangeOwnership);
EC_CREATOR(LuaEffect::f_Patrol, EFFECT_Patrol);
EC_CREATOR(LuaEffect::f_DisplayInstructions, EFFECT_DisplayInstructions);
EC_CREATOR(LuaEffect::f_ClearInstructions, EFFECT_ClearInstructions);
EC_CREATOR(LuaEffect::f_FreezeUnit, EFFECT_FreezeUnit);
EC_CREATOR(LuaEffect::f_UseAdvancedButtons, EFFECT_UseAdvancedButtons);
EC_CREATOR(LuaEffect::f_DamageObject, EFFECT_DamageObject);
EC_CREATOR(LuaEffect::f_PlaceFoundation, EFFECT_PlaceFoundation);
EC_CREATOR(LuaEffect::f_ChangeObjectName, EFFECT_ChangeObjectName);
EC_CREATOR(LuaEffect::f_ChangeObjectHP, EFFECT_ChangeObjectHP);
EC_CREATOR(LuaEffect::f_ChangeObjectAttack, EFFECT_ChangeObjectAttack);
EC_CREATOR(LuaEffect::f_StopUnit, EFFECT_StopUnit);


int LuaEffect::m_setAmount(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_Amount))
		return luaL_error(L, "Error in amount()! Effect %s cannot have an amount.", effect->types[effect->type]);
	
	lua_getnonnegative(amount, 2, "amount()");
	effect->amount=amount;
	return 0;
}


int LuaEffect::m_setLocation(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_Location))
		return luaL_error(L, "Error in location()! Effect %s cannot have a location.", effect->types[effect->type]);
	
	lua_getnonnegative(x, 2, "location()");
	lua_getnonnegative(y, 3, "location()");

	effect->location.x=x;
	effect->location.y=y;

	return 0;
}

int LuaEffect::m_setArea(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_Area))
		return luaL_error(L, "Error in area()! Effect %s cannot have an area.", effect->types[effect->type]);
	
	lua_getnonnegative(x1, 2, "area()");
	lua_getnonnegative(y1, 3, "area()");
	lua_getnonnegative(x2, 4, "area()");
	lua_getnonnegative(y2, 5, "area()");
	if (x1>x2 && y1>y2)
		return luaL_error(L, "Error in area()! Expected location (x1,y1) to be less than location (x2,y2), got (x1,y1)=(%d,%d) and (x2,y2)=(%d,%d).\nSolution: switch x1,y1 with x2,y2.", x1, y1, x2, y2);
	
	effect->area.ll.x=x1;
	effect->area.ll.y=y1;
	effect->area.ur.x=x2;
	effect->area.ur.y=y2;

	return 0;
}

int LuaEffect::m_setAIGoal(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_AIGoal))
		return luaL_error(L, "Error in ai_goal()! Effect %s cannot have an ai goal.", effect->types[effect->type]);
	
	lua_getnonnegative(ai_goal, 2, "ai_goal()");

	effect->ai_goal=ai_goal;

	return 0;
}

int LuaEffect::m_setDiplomacy(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_Diplomacy))
		return luaL_error(L, "Error in diplomacy()! Effect %s cannot have a diplomacy.", effect->types[effect->type]);
	
	//Supports string spellings
	int diplo;
	if (lua_isnumber(L, 2)) 
	{
		diplo = luaL_checknumber(L, 2);
		if (!my_util::is_diplomacy(diplo))
			return luaL_error(L, "Error in diplomacy()! Expected diplomacy name or id, got %d.", diplo);
	}
	else if (lua_isstring(L, 2))
	{
		char *diplostr=(char *)lua_tostring(L, 2);
		diplo = my_util::get_diplomacy(diplostr);
		if (diplo==-1)
			return luaL_error(L, "Error in diplomacy()! Expected diplomacy name or id, got %s.", diplo);
	}
	else
		return luaL_error(L, "Error in diplomacy()! Expected diplomacy name or id.");

	effect->diplomacy=diplo;
	
	return 0;
}

int LuaEffect::m_setDisplayTime(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_DisplayTime))
		return luaL_error(L, "Error in time()! Effect %s cannot have a time.", effect->types[effect->type]);
	
	lua_getnonnegative(display_time, 2, "display_time()");

	effect->display_time = display_time;

	return 0;
}

int LuaEffect::m_setPanel(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_Panel))
		return luaL_error(L, "Error in panel()! Effect %s cannot have a panel.", effect->types[effect->type]);
	
	int panel=luaL_checknumber(L, 2);

	if (panel>2 || panel<0)
		return luaL_error(L, "Error in panel()! Expected number from 0-2, got %d.", panel);

	effect->panel=panel;

	return 0;
}

int LuaEffect::m_setPlayerSource(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_PlayerSource))
		return luaL_error(L, "Error in player()! Effect %s cannot have a player.", effect->types[effect->type]);
	
	int player=luaL_checknumber(L, 2);

	if (player>8 || player<0)
		return luaL_error(L, "Error in player()! Expected number from 0-8, got %d.", player);

	effect->player_source=player;

	return 0;
}

int LuaEffect::m_setPlayerTarget(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_PlayerTarget))
		return luaL_error(L, "Error in player_target()! Effect %s cannot have a player_target.", effect->types[effect->type]);
	
	int player=luaL_checknumber(L, 2);

	if (player>8 || player<0)
		return luaL_error(L, "Error in player_target()! Expected number from 0-8, got %d.", player);
	
	effect->player_target=player;

	return 0;
}

int LuaEffect::m_setResource(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_Resource))
		return luaL_error(L, "Error in resource()! Effect %s cannot have a resource.", effect->types[effect->type]);
	
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

	effect->resource=id;

	return 0;
}

int LuaEffect::m_setTechnology(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_Technology))
		return luaL_error(L, "Error in technology()! Effect %s cannot have a technology.", effect->types[effect->type]);
	
	lua_getnonnegative(tech, 2, "technology()");

	effect->technology=tech;

	return 0;
}

int LuaEffect::m_setTriggerIndex(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_TriggerIndex))
		return luaL_error(L, "Error in trigger()! Effect %s cannot have a trigger id.", effect->types[effect->type]);
	
	lua_getpositive(trigger, 2, "trigger()");

	effect->trigger_index=trigger;

	return 0;
}

int LuaEffect::m_setUIDs(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_UIDs))
		return luaL_error(L, "Error in units()! Effect %s cannot have units.", effect->types[effect->type]);
	
	int i;
	for (i=0; i<MAX_UNITSEL; i++)
	{
		//when no number found, it's at the end of unit id list.
		if (!lua_isnumber(L, 2+i)) break;

		int uid=luaL_checknumber(L, 2+i);
		if (uid<0) //TODO add check for scenario unitid
			return luaL_error(L, "Error in units()! Argument #%d expected valid unit ID, got %d", 1+i, uid);
		
		//add uid to effect
		effect->uids[i]=uid;
		effect->num_selected=(i+1);
	}
	//if no units found, error
	if (i==0)
		return luaL_error(L, "Error in units()! Expected at least 1 unit ID.");
	//if >22 uids in list, throw error so the user knows that he can't list that many and have it work
	else if (lua_isnumber(L, 2+MAX_UNITSEL))
		return luaL_error(L, "Error in units()! Maximum of 22 units allowed in selection.");

	return 0;
}

int LuaEffect::m_setUIDLocation(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_UIDLocation))
		return luaL_error(L, "Error in unit_location()! Effect %s cannot have a unit_location.", effect->types[effect->type]);
	
	lua_getnonnegative(uid, 2, "unit_location()");

	effect->uid_location=uid;

	return 0;
}

int LuaEffect::m_setUnitType(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_UnitType))
		return luaL_error(L, "Error in unit_type()! Effect %s cannot have a unit type.", effect->types[effect->type]);
	
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

	effect->unit_type=id;

	return 0;
}

int LuaEffect::m_setUnitConst(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_UnitConst))
		return luaL_error(L, "Error in unit_const()! Effect %s cannot have a unit constant.", effect->types[effect->type]);
	
	lua_getnonnegative(unitconst, 2, "unit_const()");

	effect->unit_const=unitconst;

	return 0;
}

int LuaEffect::m_setUnitGroup(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_UnitGroup))
		return luaL_error(L, "Error in unit_group()! Effect %s cannot have a unit group.", effect->types[effect->type]);
	
	
	int grp=-1;
	if (lua_isstring(L, 2))
	{
		char *group=(char *)lua_tostring(L, 2);
		grp = my_util::get_ugroup(group);
		if (grp==-1)
			return luaL_error(L, "Error in unit_group()! Expected unit group name, got %s.", grp);
	}
	else
		return luaL_error(L, "Error in unit_group()! Expected unit group name.");
	
	effect->unit_group=grp;
	return 0;
}

int LuaEffect::m_setSound(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_Sound))
		return luaL_error(L, "Error in sound()! Effect %s cannot have a sound.", effect->types[effect->type]);

	const char *sound = luaL_checkstring(L, 2);	
	effect->sound.resize(strlen(sound));
	effect->sound.assign(sound);

	return 0;
}

int LuaEffect::m_setText(lua_State *L)
{
	Effect *effect = LuaUtil::getudata_effect(L, 1);
	if(!effect->valid_property(EFFECTP_Text))
		return luaL_error(L, "Error in text()! Effect %s cannot have text.", effect->types[effect->type]);

	const char *text = luaL_checkstring(L, 2);	
	effect->text.resize(strlen(text));
	effect->text.assign(text);

	return 0;
}



/** References all the functions (static, like Condition.ObjectsInArea()) for effects */
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

/** References all the methods (object-methods, non-static) for effects */
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
}