#include "LCondition.h"
#include "../genie/Condition.h"

LCondition::LCondition(Condition *c)
{
	cond = c;
}

void LCondition::checkParam(int pType) throw(char *)
{
	if (!cond->valid_property(pType))
	{
		char *err = new char[50];
		sprintf(err, "Condition_%s does not have parameter %s.", types[cond->type], partypes[pType]);
		throw(err);
	}
}

void LCondition::area(int llX, int llY, int urX, int ury) throw(char *)
{
	checkParam(CONDITIONP_Area);
}

void LCondition::amount(int amt) throw(char *)
{
	//Timer condition can use amount to set time
	if (cond->type==CONDITION_Timer)
		checkParam(CONDITIONP_Timer)
	else
		checkParam(CONDITIONP_Amount);
}

void LCondition::resource(int res) throw(char *)
{
	checkParam(CONDITIONP_ResourceType);
}

void LCondition::unit_object(int uid) throw(char *)
{
	checkParam(CONDITIONP_UIDObject);
}

void LCondition::unit_location(int uid) throw(char *)
{
	checkParam(CONDITIONP_UIDLocation);
}

void LCondition::player(int p) throw(char *)
{
	checkParam(CONDITIONP_Player);
}

void LCondition::technology(int tech) throw(char *)
{
	checkParam(CONDITIONP_Technology);
}

void LCondition::timer(int time) throw(char *)
{
	checkParam(CONDITIONP_Timer);
}

void LCondition::unit_group(int group) throw(char *)
{
	checkParam(CONDITIONP_UnitGroup);
}

void LCondition::unit_group(const char *group) throw(char *)
{
	checkParam(CONDITIONP_UnitGroup);
}

void LCondition::unit_type(int type) throw(char *)
{
	checkParam(CONDITIONP_UnitType);
}

void LCondition::unit_type(const char *type) throw(char *)
{
	checkParam(CONDITIONP_UnitType);
}

void LCondition::unit_const(int uconst) throw(char *)
{
	checkParam(CONDITIONP_UnitConst);
}

void LCondition::ai_signal(int signal) throw(char *)
{
	checkParam(CONDITIONP_AISignal);
}
