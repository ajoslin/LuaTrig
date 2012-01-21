#ifndef CONDITION_TYPES_H_
#define CONDITION_TYPES_H_

#include "Condition.h"
#include "ECTypes.h"

class Condition_None : public Condition
{
public:
	Condition_None() : Condition(CONDITION_None) {};
};

class Condition_BringObjectToArea : public Condition
{
private:
	AREA_H_FIELD;
	UIDOBJECT_H_FIELD;
public:	
	Condition_BringObjectToArea() : Condition(CONDITION_BringObjectToArea) {};
	AREA_H_FUNC;
	UIDOBJECT_H_FUNC;
};

class Condition_BringObjectToObject : public Condition
{
private:
	UIDOBJECT_H_FIELD;
	UIDLOC_H_FIELD;
public:	
	Condition_BringObjectToObject() : Condition(CONDITION_BringObjectToObject) {};
	UIDOBJECT_H_FUNC;
	UIDLOC_H_FUNC;
};

#define OWNOBJECTS_FIELDS \
	PLAYER_H_FIELD; \
	AMOUNT_H_FIELD; \
	UCONST_H_FIELD; \
	UTYPE_H_FIELD; \
	UGROUP_H_FIELD
#define OWNOBJECTS_FUNCS \
	PLAYER_H_FUNC; \
	AMOUNT_H_FUNC; \
	UCONST_H_FUNC; \
	UTYPE_H_FUNC; \
	UGROUP_H_FUNC

class Condition_OwnObjects : public Condition
{
private:
	OWNOBJECTS_FIELDS;
public:
	Condition_OwnObjects() : Condition(CONDITION_OwnObjects) {};
	OWNOBJECTS_FUNCS;
};

class Condition_OwnFewerObjects : public Condition
{
private:
	OWNOBJECTS_FIELDS;
public:
	Condition_OwnFewerObjects() : Condition(CONDITION_OwnFewerObjects) {};
	OWNOBJECTS_FUNCS;
};

class Condition_ObjectsInArea : public Condition
{
private:
	OWNOBJECTS_FIELDS;
	AREA_H_FIELD;
public:
	Condition_ObjectsInArea() : Condition(CONDITION_ObjectsInArea) {};
	OWNOBJECTS_FUNCS;
	AREA_H_FUNC;
};

class Condition_DestroyObject : public Condition
{
private:
	UIDOBJECT_H_FIELD;
public:	
	Condition_DestroyObject() : Condition(CONDITION_DestroyObject) {};
	UIDOBJECT_H_FUNC;
};

class Condition_CaptureObject : public Condition
{
private:
	UIDOBJECT_H_FIELD;
	PLAYER_H_FIELD;
public:	
	Condition_CaptureObject() : Condition(CONDITION_CaptureObject) {};
	UIDOBJECT_H_FUNC;
	PLAYER_H_FUNC;
};

class Condition_AccumulateAttribute : public Condition
{
private:
	PLAYER_H_FIELD;
	RESOURCE_H_FIELD;
	AMOUNT_H_FIELD;
public:	
	Condition_AccumulateAttribute() : Condition(CONDITION_AccumulateAttribute) {};
	PLAYER_H_FUNC;
	RESOURCE_H_FUNC;
	AMOUNT_H_FUNC;
};

class Condition_ResearchTechnology : public Condition
{
private:
	PLAYER_H_FIELD;
	TECH_H_FIELD;
public:	
	Condition_ResearchTechnology() : Condition(CONDITION_ResearchTechnology) {};
	PLAYER_H_FUNC;
	TECH_H_FUNC;
};

class Condition_Timer : public Condition
{
private:
	TIMER_H_FIELD;
public:	
	Condition_Timer() : Condition(CONDITION_Timer) {};
	TIMER_H_FUNC;
};

class Condition_ObjectSelected : public Condition
{
private:
	UIDOBJECT_H_FIELD;
public:	
	Condition_ObjectSelected() : Condition(CONDITION_ObjectSelected) {};
	UIDOBJECT_H_FUNC;
};

class Condition_AISignal : public Condition
{
private:
	AISIGNAL_H_FIELD;
public:	
	Condition_AISignal() : Condition(CONDITION_AISignal) {};
	AISIGNAL_H_FUNC;
};

class Condition_PlayerDefeated : public Condition
{
private:
	PLAYER_H_FIELD;
public:	
	Condition_PlayerDefeated() : Condition(CONDITION_PlayerDefeated) {};
	PLAYER_H_FUNC;
};

class Condition_ObjectHasTarget : public Condition
{
private:
	UIDOBJECT_H_FIELD;
	UIDLOC_H_FIELD;
public:	
	Condition_ObjectHasTarget() : Condition(CONDITION_ObjectHasTarget) {};
	UIDOBJECT_H_FUNC;
	UIDLOC_H_FUNC;
};

class Condition_ObjectVisible : public Condition
{
private:
	UIDOBJECT_H_FIELD;
public:	
	Condition_ObjectVisible() : Condition(CONDITION_ObjectVisible) {};
	UIDOBJECT_H_FUNC;
};

class Condition_ObjectNotVisible : public Condition
{
private:
	UIDOBJECT_H_FIELD;
public:	
	Condition_ObjectNotVisible() : Condition(CONDITION_ObjectNotVisible) {};
	UIDOBJECT_H_FUNC;
};

class Condition_ResearchingTechnology : public Condition
{
private:
	TECH_H_FIELD;
public:	
	Condition_ResearchingTechnology() : Condition(CONDITION_ResearchingTechnology) {};
	TECH_H_FUNC;
};

class Condition_UnitsGarrisoned : public Condition
{
private:
	UIDOBJECT_H_FUNC;
	AMOUNT_H_FUNC;
public:	
	Condition_UnitsGarrisoned() : Condition(CONDITION_UnitsGarrisoned) {};
	UIDOBJECT_H_FIELD;
	AMOUNT_H_FIELD;
};

class Condition_DifficultyLevel : public Condition
{
private:
	AMOUNT_H_FUNC;
public:	
	Condition_DifficultyLevel() : Condition(CONDITION_DifficultyLevel) {};
	AMOUNT_H_FIELD;
};

#endif



