#ifndef CONDITION_H_
#define CONDITION_H_ 

#include <stdio.h>
#include <string>
using namespace std;
#include "../include/aokutil.h"

#define MAX_CONDITION CONDITION_DifficultyLevel
#define NUM_CONDS	20

enum ConditionType
{
	CONDITION_None,
	CONDITION_BringObjectToArea,
	CONDITION_BringObjectToObject,
	CONDITION_OwnObjects,
	CONDITION_OwnFewerObjects,
	CONDITION_ObjectsInArea,
	CONDITION_DestroyObject,
	CONDITION_CaptureObject,
	CONDITION_AccumulateAttribute,
	CONDITION_ResearchTechnology,
	CONDITION_Timer,
	CONDITION_ObjectSelected,
	CONDITION_AISignal,
	CONDITION_PlayerDefeated,
	CONDITION_ObjectHasTarget,
	CONDITION_ObjectVisible,
	CONDITION_ObjectNotVisible,
	CONDITION_ResearchingTechnology,
	CONDITION_UnitsGarrisoned,
	CONDITION_DifficultyLevel,
};

enum ConditionProperty
{
	CONDITIONP_Amount,
	CONDITIONP_ResourceType,
	CONDITIONP_UIDObject,
	CONDITIONP_UIDLocation,
	CONDITIONP_Player,
	CONDITIONP_Technology,
	CONDITIONP_Timer,
	CONDITIONP_Area,
	CONDITIONP_UnitGroup,
	CONDITIONP_UnitType,
	CONDITIONP_UnitConst,
	CONDITIONP_AISignal,
};

class Condition 
{
public:
	Condition();

	int readfromscx(FILE *in);
	void writetoscx(FILE *out);
	void writetolua(FILE *out, const char *trigvar, const char* condvar);

	const std::string getName() const;

	bool check() const;
	bool valid_property(ConditionProperty) const;

	AOKRECT area;
	long type;
	long check_value;
	long amount;
	long resource_type;
	long uid_object;
	long uid_location;
	long player;
	long technology;
	long timer;
	long unknown;
	long unit_group;
	long unit_type;
	long unit_const;
	long ai_signal;

//internal

	static const char* types[NUM_CONDS];
};

#endif