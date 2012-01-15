#include "LEffect.h"
#include "../genie/Effect.h"
#include <algorithm>

LEffect::LEffect(Effect *e, int eId, int trigId)
{
	this->eId=eId;
	this->trigId=trigId;
	effect = e;
}

bool LEffect::checkParam(EffectProperty p)
{
	return effect->valid_property(p);
}

void LEffect::paramError(EffectProperty p) throw(char *)
{
	throwEffectError("Effect%s cannot have parameter %s.", eId, trigId, effect->types[effect->type], effect->propertyTypes[p]);
}

void LEffect::location(int x, int y) throw(char *)
{
	if (!checkParam(EFFECTP_Location))
		return paramError(EFFECTP_Location);

	effect->location.x=std::max(-1, x);
	effect->location.y=std::max(-1, y);
}

void LEffect::area(int llX, int llY, int urX, int urY) throw(char *)
{
	if (!checkParam(EFFECTP_Area))
		return paramError(EFFECTP_Area);
	
	effect->area.ll.x=std::max(-1, llX);
	effect->area.ll.y=std::max(-1, llY);
	effect->area.ur.x=std::max(-1, urX);
	effect->area.ur.y=std::max(-1, urY);
}

void LEffect::ai_goal(int goal) throw(char *)
{
	if (!checkParam(EFFECTP_AIGoal))
		return paramError(EFFECTP_AIGoal);

	effect->ai_goal=std::max(-1, goal);
}

void LEffect::amount(int amt) throw(char *)
{
	if (!checkParam(EFFECTP_Amount))
		return paramError(EFFECTP_Amount);

	if (amt==-1)
	{
		throwEffectError("amount() expected any value not equal to -1, got %d.", amt);
		return;
	}
	effect->amount=amt;
}

void LEffect::diplomacy(int diplo) throw(char *)
{
	if (!checkParam(EFFECTP_Diplomacy))
		return paramError(EFFECTP_Diplomacy);
	
	if (!genieDiplomacies->has(diplo))
	{
		throwEffectError("diplomacy() expected diplomacy ID or name, got %d.", diplo);
		return;
	}
	effect->diplomacy=diplo;
}

void LEffect::diplomacy(const char *diplo) throw(char *)
{
	if (!checkParam(EFFECTP_Diplomacy))
		return paramError(EFFECTP_Diplomacy);
	
	if (!genieDiplomacies->has(diplo))
	{
		throwEffectError("diplomacy() expected diplomacy ID or name, got %s.", diplo);
		return;
	}
	effect->diplomacy=genieDiplomacies->idFromName(diplo);
}

void LEffect::time(int t) throw(char *)
{
	if (!checkParam(EFFECTP_DisplayTime))
		return paramError(EFFECTP_DisplayTime);

	effect->display_time=std::max(0, t);
}

void LEffect::panel(int p) throw(char *)
{
	if (!checkParam(EFFECTP_Panel))
		return paramError(EFFECTP_Panel);

	if (p<0 || p>2)
	{
		throwEffectError("panel() expected panel between 0 and 2, got %d.", p);
		return;
	}
	effect->panel=p;
}

void LEffect::player_source(int p) throw(char *)
{
	if (!checkParam(EFFECTP_PlayerSource))
		return paramError(EFFECTP_PlayerSource);
	
	if (p<0 || p>8)
	{
		throwEffectError("player_source() expected player value between 0 and 8, got %d.", p);
		return;
	}
	effect->player_source = p;
}

void LEffect::p_source(int p) throw(char *)
{
	player_source(p);
}

void LEffect::player_target(int p) throw(char *)
{
	if (!checkParam(EFFECTP_PlayerTarget))
		return paramError(EFFECTP_PlayerTarget);
	
	if (p<0 || p>8)
	{
		throwEffectError("player_source() expected player value between 0 and 8, got %d.", p);
		return;
	}
	effect->player_target = p;
}

void LEffect::p_target(int p) throw(char *)
{
	player_target(p);
}

void LEffect::resource(int res) throw(char *)
{
	if (!checkParam(EFFECTP_Resource))
		return paramError(EFFECTP_Resource);
	
	if (!genieResources->has(res))
	{
		throwEffectError("resource() expected resource ID or name, got %d.", res);
		return;
	}

	effect->resource=res;
}

void LEffect::resource(const char *res) throw(char *)
{
	if (!checkParam(EFFECTP_Resource))
		return paramError(EFFECTP_Resource);
	
	if (!genieResources->has(res))
	{
		throwEffectError("resource() expected resource ID or name, got %s.", res);
		return;
	}
	
	effect->resource = genieResources->idFromName(res);
}

void LEffect::technology(int t) throw(char *)
{
	if (!checkParam(EFFECTP_Technology))
		return paramError(EFFECTP_Technology);
	
	if (t<0)
	{
		throwEffectError("technology() expected technology ID, got %d.", t);
		return;
	}
	effect->technology = t;
}

void LEffect::tech(int t) throw(char *)
{
	technology(t);
}

void LEffect::trigger(int trig) throw(char *)
{
	if (!checkParam(EFFECTP_TriggerIndex))
		return paramError(EFFECTP_TriggerIndex);
	
	effect->trigger_index=std::max(-1, trig);
}

#define unitcheck(var, index) \
	if (var!=-1) \
	{ \
		effect->uids[index]=var; \
		num_sel++; \
	} \

void LEffect::units(int u1,int u2,int u3,int u4,int u5,int u6,int u7,
	int u8,int u9,int u10,int u11,int u12,int u13,int u14,int u15,
	int u16,int u17,int u18,int u19,int u20,int u21,int u22) throw(char *)
{
	if (!checkParam(EFFECTP_UIDs))
		return paramError(EFFECTP_UIDs);
	
	int num_sel=0;
	unitcheck(u1,  0);
	unitcheck(u2,  1);
	unitcheck(u3,  2);
	unitcheck(u4,  3);
	unitcheck(u5,  4);
	unitcheck(u6,  5);
	unitcheck(u7,  6);
	unitcheck(u8,  7);
	unitcheck(u9,  8);
	unitcheck(u10, 9);
	unitcheck(u11, 10);
	unitcheck(u12, 11);
	unitcheck(u13, 12);
	unitcheck(u14, 13);
	unitcheck(u15, 14);
	unitcheck(u16, 15);
	unitcheck(u17, 16);
	unitcheck(u18, 17);
	unitcheck(u19, 18);
	unitcheck(u20, 19);
	unitcheck(u21, 20);
	unitcheck(u22, 21);	

	effect->num_selected = num_sel;
}

void LEffect::unit_location(int uid) throw(char *)
{
	if (!checkParam(EFFECTP_UIDLocation))
		return paramError(EFFECTP_UIDLocation);
	
	effect->uid_location=std::max(-1, uid);
}

void LEffect::unit_group(int group) throw(char *)
{
	if (!checkParam(EFFECTP_UnitGroup))
		return paramError(EFFECTP_UnitGroup);
	
	if (!genieUnitGroups->has(group))
	{
		throwEffectError("unit_group() expected unit group ID or name, got %d.", group);
		return;
	}
	effect->unit_group=group;
}

void LEffect::unit_group(const char *group) throw(char *)
{
	if (!checkParam(EFFECTP_UnitGroup))
		return paramError(EFFECTP_UnitGroup);
	
	if (!genieUnitGroups->has(group))
	{
		throwEffectError("unit_group() expected unit group ID or name, got %s.", group);
		return;
	}
	effect->unit_group=genieUnitGroups->idFromName(group);
}

void LEffect::unit_type(int type) throw(char *)
{
	if (!checkParam(EFFECTP_UnitType))
		return paramError(EFFECTP_UnitType);
	
	if (!genieUnitTypes->has(type))
	{
		throwEffectError("unit_type() expected unit type ID or name, got %d.", type);
		return;
	}
	effect->unit_type=type;
}

void LEffect::unit_type(const char *type) throw(char *)
{
	if (!checkParam(EFFECTP_UnitType))
		return paramError(EFFECTP_UnitType);
	
	if (!genieUnitTypes->has(type))
	{
		throwEffectError("unit_type() expected unit type ID or name, got %s.", type);
		return;
	}
	effect->unit_type=genieUnitTypes->idFromName(type);
}

void LEffect::unit_const(int uconst) throw(char *)
{
	if (!checkParam(EFFECTP_UnitConst))
		return paramError(EFFECTP_UnitConst);

	effect->unit_const=std::max(-1, uconst);
}

void LEffect::text(const char *text) throw(char *)
{
	if (!checkParam(EFFECTP_Text))
		return paramError(EFFECTP_Text);
	
	effect->text.resize(strlen(text)+1);
	effect->text.assign(text);
	effect->text+='\0';
}

void LEffect::sound(const char *sound) throw(char *)
{
	if (!checkParam(EFFECTP_Sound))
		return paramError(EFFECTP_Sound);
	
	effect->sound.resize(strlen(sound)+1);
	effect->sound.assign(sound);
	effect->text+='\0';
}
