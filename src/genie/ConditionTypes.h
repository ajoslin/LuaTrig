#ifndef CONDITION_TYPES_H_
#define CONDITION_TYPES_H_

#include "Condition.h"

class Condition_None : public Condition
{
};

class Condition_BringObjectToArea : public Condition
{
private:
	AOKRECT ar;
	long uid;
public:	
	void uid_object(int);
	void area(int, int, int, int);
};

class Condition_BringObjectToObject : public Condition
{
private:
	long uid_o;
	long uid_l;
public:	
	void uid_object(int);
	void uid_location(int);
};

class Condition_OwnObjects : public Condition
{
private:
	long pl;
	long amt;
	long uconst;
	long utype;
	long ugroup;
public:	
	void player(int);
	void amount(int);
	void unit_const(int);
	void unit_type(int);
	void unit_type(const char *);
	void unit_group(int);
	void unit_group(const char *);
};

class Condition_OwnFewerObjects : public Condition
{
private:
	long pl;
	long amt;
	long uconst;
	long utype;
	long ugroup;
public:	
	void player(int);
	void amount(int);
	void unit_const(int);
	void unit_type(int);
	void unit_type(const char *);
	void unit_group(int);
	void unit_group(const char *);
};

class Condition_ObjectsInArea : Condition_OwnObjects_OwnFewerObjects
{
private:
	AOKRECT ar;
	long pl;
	long amt;
	long uconst;
	long utype;
	long ugroup;
public:	
	void area(int, int, int, int);
	void player(int);
	void amount(int);
	void unit_const(int);
	void unit_type(int);
	void unit_type(const char *);
	void unit_group(int);
	void unit_group(const char *);
};

class Condition_DestroyObject : public Condition
{
private:
	long uid;
public:	
	void uid_object(int);
};

class Condition_CaptureObject : public Condition
{
private:
	long uid;
	long pl;
public:	
	void uid_object(int);
	void player(int);
};

class Condition_AccumulateAttribute : public Condition
{
private:
	long pl;
	long res;
	long amt;
public:	
	void player(int);
	void resource(int);
	void resource(const char *);
	void amount(int);
};

class Condition_ResearchTechnology : public Condition
{
private:
	long pl;
	long tech;
public:	
	void player(int);
	void technology(int);
	void tech(int);
};

class Condition_Timer : public Condition
{
private:
	long time;
public:	
	void time(int);
	void amount(int);
};

class Condition_ObjectSelected : public Condition
{
private:
	long uid;
public:	
	void uid_object(int);
};

class Condition_AISignal : public Condition
{
private:
	long signal;
public:	
	void ai_signal(int);
};

class Condition_PlayerDefeated : public Condition
{
private:
	long pl;
public:	
	void player(int);
};

class Condition_ObjectHasTarget : public Condition
{
private:
	long uid_o;
	long uid_l;
	long uconst;
	long utype;
	long ugroup;
public:	
	void uid_object(int);
	void uid_location(int);
	void unit_type(int);
	void unit_type(const char *);
	void unit_group(int);
	void unit_group(const char *);
};

class Condition_ObjectVisible : public Condition
{
private:
	long uid;
public:	
	void uid_object(int);
};

class Condition_ObjectNotVisible : public Condition
{
private:
	long uid;
public:	
	void uid_object(int);
};

class Condition_ResearchTechnology : public Condition
{
private:
	long pl;
	long tech;
public:	
	void player(int);
	void technology(int);
	void tech(int);
};

class Condition_UnitsGarrisoned : public Condition
{
private:
	long uid;
	long amt;
public:	
	void uid_object(int);
	void amount(int);
};

class Condition_DifficultyLevel : public Condition
{
private:
	long amt;
public:	
	void amount(int);
};



#endif
