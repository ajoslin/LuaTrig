#ifndef CONDITION_H_
#define CONDITION_H_ 

#include <stdio.h>
#include <string>
#include "aok_types.h"

#define MAX_CONDITION 	CONDITION_DifficultyLevel
#define NUM_CONDS		20
#define NUM_COND_PARAMS	12

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

	const char *getName();

	void read(FILE *in);
	void write(FILE *out);

	bool check();
	bool valid_property(ConditionProperty);
	
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
	static const char* partypes[NUM_COND_PARAMS];
};

#endif