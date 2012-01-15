#ifndef CONDITION_TYPES_H_
#define CONDITION_TYPES_H_

#include "Condition.h"
#include "ECTypes.h"

class Condition_None : public Condition
{
};

class Condition_BringObjectToArea : public Condition
{
private:
	AREA_H_FIELD;
	UIDOBJECT_H_FIELD;
public:	
	AREA_H_FUNC;
	UIDOBJECT_H_FUNC;
};

class Condition_BringObjectToObject : public Condition
{
private:
	UIDOBJECT_H_FIELD;
	UIDLOCATION_H_FIELD;
public:	
	void uid_object(int);
	void uid_location(int);
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
	OWNOBJECTS_FUNCS;
};

class Condition_OwnFewerObjects : public Condition
{
private:
	OWNOBJECTS_FIELDS;
public:
	OWNOBJECTS_FUNCS;
};

class Condition_ObjectsInArea : Condition_OwnObjects_OwnFewerObjects
{
private:
	OWNOBJECTS_FIELDS;
	AREA_H_FIELD;
public:
	OWNOBJECTS_FUNCS;
	AREA_H_FUNC;
};

class Condition_DestroyObject : public Condition
{
private:
	UIDOBJECT_H_FIELD;
public:	
	UIDOBJECT_H_FUNC;
};

class Condition_CaptureObject : public Condition
{
private:
	UIDOBJECT_H_FIELD;
	PLAYER_H_FIELD;
public:	
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
	PLAYER_H_FUNC;
	TECH_H_FUNC;
};

class Condition_Timer : public Condition
{
private:
	TIMER_H_FIELD;
public:	
	TIMER_H_FUNC;
};

class Condition_ObjectSelected : public Condition
{
private:
	UIDOBJECT_H_FIELD;
public:	
	UIDOBJECT_H_FUNC;
};

class Condition_AISignal : public Condition
{
private:
	AISIGNAL_H_FIELD;
public:	
	AISIGNAL_H_FUNC;
};

class Condition_PlayerDefeated : public Condition
{
private:
	PLAYER_H_FIELD;
public:	
	PLAYER_H_FUNC;
};

class Condition_ObjectHasTarget : public Condition
{
private:
	UIDOBJECT_H_FIELD;
	UIDLOCATION_H_FIELD;
public:	
	UIDOBJECT_H_FUNC;
	UIDLOCATION_H_FUNC;
};

class Condition_ObjectVisible : public Condition
{
private:
	UIDOBJECT_H_FIELD;
public:	
	UIDOBJECT_H_FUNC;
};

class Condition_ObjectNotVisible : public Condition
{
private:
	UIDOBJECT_H_FIELD;
public:	
	UIDOBJECT_H_FUNC;
};

class Condition_ResearchTechnology : public Condition
{
private:
	TECH_H_FIELD;
public:	
	TECH_H_FUNC;
};

class Condition_UnitsGarrisoned : public Condition
{
private:
	UIDOBJECT_H_FUNC;
	AMOUNT_H_FUNC;
public:	
	UIDOBJECT_H_FIELD;
	AMOUNT_H_FIELD;
};

class Condition_DifficultyLevel : public Condition
{
private:
	AMOUNT_H_FUNC;
public:	
	AMOUNT_H_FIELD;
};



#endif
