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
	CONDITIONP_Resource,
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
private:
	long type;
	long check_value;

	AOKRECT area;
	
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

public:
	Condition(long type);

	const char *getName();

	void read(FILE *in);
	void write(FILE *out);

	bool check();

	virtual long getType() { return type; }

	virtual long getAmount() { return -1; }
	virtual long getResource() { return -1; }
	virtual long getUidObject() { return -1; }
	virtual long getUidLocation() { return -1; }
	virtual long getPlayer() { return -1; }
	virtual long getTechnology() { return -1; }
	virtual long getTimer() { return -1; }
	virtual AOKRECT getArea() { return AOKRECT(); }
	virtual long getUnitGroup() { return -1; }
	virtual long getUnitType() { return -1; }
	virtual long getUnitConst() { return -1; }
	virtual long getAISignal() { return -1; }

	static const char* types[NUM_CONDS];
	static const char* propertyTypes[NUM_COND_PARAMS];
};

#endif