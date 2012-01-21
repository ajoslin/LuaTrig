#ifndef CONDITION_H_
#define CONDITION_H_ 

#include "aok_types.h"
#include "util_file.h"
#include <stdio.h>
#include <string>

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
	//always -1
	long unknown;

public:
	Condition(long type);
	static Condition *createType(long type=0);

	const char *getName();

	void read(FILE *in);
	void write(FILE *out);

	bool check();

	//getters: return null values by default. inherited condition types override these as appropriate
	virtual long getAmount() { return -1; };
	virtual long getResource() { return -1; };
	virtual long getUidObject() { return -1; };
	virtual long getUidLocation() { return -1; };
	virtual long getPlayer() { return -1; };
	virtual long getTechnology() { return -1; };
	virtual long getTimer() { return -1; };
	virtual AOKRECT getArea() { return AOKRECT(); };
	virtual long getUnitGroup() { return -1; };
	virtual long getUnitType() { return -1; };
	virtual long getUnitConst() { return -1; };
	virtual long getAiSignal() { return -1; };

	//readers: return null values by default. also overridden by inherited condition types.
	//these are not virtual because inherited classes simply override and don't want the above functionality
	virtual void readAmount(FILE *in) { fskip(in, 4); };
	virtual void readResource(FILE *in) { fskip(in, 4); };
	virtual void readUidObject(FILE *in) { fskip(in, 4); };
	virtual void readUidLocation(FILE *in) { fskip(in, 4); };
	virtual void readPlayer(FILE *in) { fskip(in, 4); };
	virtual void readTechnology(FILE *in) { fskip(in, 4); };
	virtual void readTimer(FILE *in) { fskip(in, 4); };
	virtual void readArea(FILE *in) { fskip(in, 16); };
	virtual void readUnitGroup(FILE *in) { fskip(in, 4); };
	virtual void readUnitType(FILE *in) { fskip(in, 4); };
	virtual void readUnitConst(FILE *in) { fskip(in, 4); };
	virtual void readAiSignal(FILE *in) { fskip(in, 4); };

	static const char* types[NUM_CONDS];
	static const char* propertyTypes[NUM_COND_PARAMS];
};

#endif



