#include "LCondition.h"
#include "util_lua.h"
#include "../genie/aok_types.h"
#include <algorithm>

//throw an error with cond prefix and given text
#define throwCondError(...) \
	char *err = new char[100]; \
	sprintf(err, "Error in Trigger %d, Condition %d: ", trigId, cId); \
	sprintf(err, __VA_ARGS__); \
	throw(err)

LCondition::LCondition(Condition *c, int cId, int trigId)
{
	this->cId=cId;
	this->trigId=trigId;
	cond = c;
}

bool LCondition::checkParam(ConditionProperty p)
{
	return cond->valid_property(p);
}

void LCondition::paramError(ConditionProperty p) throw(char *)
{
	throwCondError("condition_%s cannot have parameter %s.", cId, trigId, cond->types[cond->type], cond->partypes[p]);
}

void LCondition::area(int llX, int llY, int urX, int urY) throw(char *)
{
	if (!checkParam(CONDITIONP_Area))
		return paramError(CONDITIONP_Area);
	
	cond->area.ll.x=std::max(-1, llX);
	cond->area.ll.y=std::max(-1, llY);
	cond->area.ur.x=std::max(-1, urX);
	cond->area.ur.y=std::max(-1, urY);
}

void LCondition::amount(int amt) throw(char *)
{
	//Timer condition can use amount to set time
	if (!checkParam(CONDITIONP_Amount)) 
		return paramError(CONDITIONP_Amount);
	
	if (amt==-1)
	{
		throwCondError("amount() expected any value not equal to -1, got %d.", amt);
		return;
	}
	cond->amount=amt;
}

void LCondition::resource(int res) throw(char *)
{
	if (!checkParam(CONDITIONP_ResourceType))
		return paramError(CONDITIONP_ResourceType);
	
	if (!genieResources->has(res))
	{
		throwCondError("resource() expected resource ID or name, got %d.", res);
		return;
	}

	cond->resource_type=res;
}

void LCondition::resource(const char *res) throw(char *)
{
	if (!checkParam(CONDITIONP_ResourceType))
		return paramError(CONDITIONP_ResourceType);
	
	if (!genieResources->has(res))
	{
		throwCondError("resource() expected resource ID or name, got %s.", res);
		return;
	}
	
	cond->resource_type = genieResources->idFromName(res);
}

void LCondition::unit_object(int uid) throw(char *)
{
	if (!checkParam(CONDITIONP_UIDObject))
		return paramError(CONDITIONP_UIDObject);
	
	cond->uid_object = std::max(uid, -1);
}

void LCondition::unit_location(int uid) throw(char *)
{
	if (!checkParam(CONDITIONP_UIDLocation))
		return paramError(CONDITIONP_UIDLocation);
	
	cond->uid_location = std::max(uid, -1);
}

void LCondition::player(int p) throw(char *)
{
	if (!checkParam(CONDITIONP_Player))
		return paramError(CONDITIONP_Player);
	
	if (p<0 || p>8)
	{
		throwCondError("player() expected player value between 0 and 8, got %d.", p);
		return;
	}
	cond->player = p;
}

void LCondition::technology(int tech) throw(char *)
{
	if (!checkParam(CONDITIONP_Technology))
		return paramError(CONDITIONP_Technology);

	if (tech<0)
	{
		throwCondError("technology() expected technology ID, got %d.", tech);
		return;
	}
	cond->technology = tech;
}

void LCondition::timer(int time) throw(char *)
{
	if (!checkParam(CONDITIONP_Timer))
		return paramError(CONDITIONP_Timer);
	
	if (time<0)
	{
		throwCondError("timer() expected time >=0, got %d.", time);
		return;
	}
	cond->timer = time;
}

void LCondition::unit_group(int group) throw(char *)
{
	if (!checkParam(CONDITIONP_UnitGroup))
		return paramError(CONDITIONP_UnitGroup);
	
	if (!genieUnitGroups->has(group))
	{
		throwCondError("unit_group() expected unit group ID or name, got %d.", group);
		return;
	}
	cond->unit_group=group;
}

void LCondition::unit_group(const char *group) throw(char *)
{
	if (!checkParam(CONDITIONP_UnitGroup))
		return paramError(CONDITIONP_UnitGroup);
	
	if (!genieUnitGroups->has(group))
	{
		throwCondError("unit_group() expected unit group ID or name, got %s.", group);
		return;
	}
	cond->unit_group=genieUnitGroups->idFromName(group);
}

void LCondition::unit_type(int type) throw(char *)
{
	if (!checkParam(CONDITIONP_UnitType))
		return paramError(CONDITIONP_UnitType);
	
	if (!genieUnitTypes->has(type))
	{
		throwCondError("unit_type() expected unit type ID or name, got %d.", type);
		return;
	}
	cond->unit_type=type;
}

void LCondition::unit_type(const char *type) throw(char *)
{
	if (!checkParam(CONDITIONP_UnitType))
		return paramError(CONDITIONP_UnitType);
	
	if (!genieUnitTypes->has(type))
	{
		throwCondError("unit_type() expected unit type ID or name, got %s.", type);
		return;
	}
	cond->unit_type=genieUnitTypes->idFromName(type);
}

void LCondition::unit_const(int uconst) throw(char *)
{
	if (!checkParam(CONDITIONP_UnitConst))
		return paramError(CONDITIONP_UnitConst);
	
	cond->unit_const=std::max(uconst, -1);
}

void LCondition::ai_signal(int signal) throw(char *)
{
	if (!checkParam(CONDITIONP_AISignal))
		return paramError(CONDITIONP_AISignal);

	cond->ai_signal=std::max(signal, -1);
}
