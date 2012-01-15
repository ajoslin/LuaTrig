#ifndef EFFECT_TYPES_H_
#define EFFECT_TYPES_H_

#include "Effect.h"
#include <string>
#include <vector>

//max 22
//listed here because swig variable args support is bad
#define EFF_UNITS_INTLIST int a, int b=-1, int c=-1, int d=-1, int e=-1, int f=-1, int g=-1, int h=-1, int i=-1, int j=-1, int k=-1, int l=-1, int m=-1, int o=-1, int p=-1, int q=-1, int r=-1, int s=-1, int t=-1, int u=-1, int v=-1

#define AMOUNT_H_FIELD 		long amt
#define LOCATION_H_FIELD 	long loc
#define AREA_H_FIELD		long ar
#define AIGOAL_H_FIELD		long aigoal
#define DIPLO_H_FIELD		long diplo
#define DISPTIME_H_FIELD	long disptime
#define PANEL_H_FIELD		long pan
#define PSOURCE_H_FIELD		long pl_source
#define PTARGET_H_FIELD		long pl_target;
#define RESOURCE_H_FIELD	long res
#define TECH_H_FIELD		long tec
#define TRIGGER_H_FIELD		long trig
#define UIDS_H_FIELD		std::vector<int> uids
#define UIDLOC_H_FIELD		long uloc
#define UGROUP_H_FIELD		long ugroup
#define UTYPE_H_FIELD		long utype
#define UCONST_H_FIELD		long uconst
#define SOUND_H_FIELD		std::string snd
#define TEXT_H_FIELD		std::string txt

#define AMOUNT_H_FUNC 		void amount(int)
#define LOCATION_H_FUNC 	void location(int, int)
#define AREA_H_FUNC			void area(int, int, int, int)
#define AIGOAL_H_FUNC		void ai_goal(int, int, int, int)
#define DIPLO_H_FUNC		void diplomacy(int); void diplomacy(const char *)
#define DISPTIME_H_FUNC		void display_time(int, int, int, int)
#define PANEL_H_FUNC		void panel(int, int)
#define PSOURCE_H_FUNC		void p_source(int)
#define PTARGET_H_FUNC		void p_target(int)
#define RESOURCE_H_FUNC		void resource(int); void reosurce(const char *)
#define TECH_H_FUNC			void technology(int); void tech(int)
#define TRIGGER_H_FUNC		void trigger(int)
#define UIDS_H_FUNC			void units(EFF_UNITS_INTLIST)
#define UIDLOC_H_FUNC		void uid_location(int)
#define UGROUP_H_FUNC		void unit_group(int); void unit_group(const char *)
#define UTYPE_H_FUNC		void unit_type(int); void unit_type(const char *)
#define UCONST_H_FUNC		void unit_const(int)
#define SOUND_H_FUNC		void sound(const char *)
#define TEXT_H_FUNC			void text(const char *)


class Effect_None : public Effect
{
};

class Effect_ChangeDiplomacy : public Effect
{
private:
	PSOURCE_H_FIELD;
	PTARGET_H_FIELD;
	DIPLO_H_FIELD;
public:	
	void p_source(int);
	void p_target(int);
	void diplomacy(int);
	void diplomacy(const char *);
};

class Effect_ResearchTechnology : public Effect
{
private:
	PSOURCE_H_FIELD;
	TECH_H_FIELD;
public:	
	void p_source(int);
	void technology(int);
	void tech(int);
};

class Effect_SendChat : public Effect
{
private:
	PSOURCE_H_FIELD;
	TEXT_H_FIELD;
	SOUND_H_FIELD;
public:	
	void p_source(int);
	void text(const char *);
	void sound(const char *);
};

class Effect_PlaySound : public Effect
{
private:
	PSOURCE_H_FIELD;
	std::string snd;
public:	
	void p_source(int);
	void sound(const char *);
};

class Effect_SendTribute : public Effect
{
private:
	PSOURCE_H_FIELD;
	PTARGET_H_FIELD;
	long res;
	long amt;
public:	
	void p_source(int);
	void p_target(int);
	void resource(int);
	void resource(const char *);
	void amount(int);
};

class Effect_UnlockGate : public Effect
{
private:
	std::vector<int> uids;
public:	
	void units(EFF_UNITS_INTLIST);
};

class Effect_LockGate : public Effect
{
private:
	std::vector<int> uids;
public:	
	void units(EFF_UNITS_INTLIST);
};

class Effect_ActivateTrigger : public Effect
{
private:
	int trig;
public:	
	void trigger(int);
};

class Effect_DeactivateTrigger : public Effect
{
private:
	int trig;
public:	
	void trigger(int);
};

class Effect_AIScriptGoal : public Effect
{
private:
	int goal;
	PSOURCE_H_FIELD;
public:	
	void p_source(int);
	void ai_goal(int);
};

class Effect_CreateObject : public Effect
{
private:
	int uid;
	int loc;
	PSOURCE_H_FIELD;
public:	
	void p_source(int);
	void unit_const(int);
	void location(int, int);
};

#define TASK_OBJECT_H \
private: \
	std::vector<int> uids; \
	int uid_l; \
	PSOURCE_H_FIELD;
	AOKRECT ar; \
	AOKPT loc; \
	int ugroup; \
	int utype; \
	int uconst; \
public:	 \
	void p_source(int); \
	void units(EFF_UNITS_INTLIST); \
	void uid_location(int); \
	void location(int, int); \
	void area(int, int, int, int); \
	void unit_group(int); \
	void unit_group(const char *); \
	void unit_type(int); \
	void unit_type(const char *); \
	void unit_const(int)

class Effect_TaskObject : public Effect
{
	TASK_OBJECT_H;
};

class Effect_DeclareVictory : public Effect
{
private:
	PSOURCE_H_FIELD;
public:	
	void p_source(int);
};

class Effect_KillObject : public Effect
{
	TASK_OBJECT_H;
};

class Effect_RemoveObject : public Effect
{
	TASK_OBJECT_H;
};

class Effect_ChangeView : public Effect
{
private:
public:	
};

class Effect_Unload : public Effect
{
private:
public:	
};

class Effect_ChangeOwnership : public Effect
{
private:
public:	
};

class Effect_Patrol : public Effect
{
private:
public:	
};

class Effect_DisplayInstructions : public Effect
{
private:
public:	
};

class Effect_ClearInstructions : public Effect
{
private:
public:	
};

class Effect_FreezeUnit : public Effect
{
	TASK_OBJECT_H;
};

class Effect_UseAdvancedButtons : public Effect
{
private:
public:	
};

class Effect_DamageObject : public Effect
{
private:
public:	
};

class Effect_PlaceFoundation : public Effect
{
private:
public:	
};

class Effect_ChangeObjectName : public Effect
{
private:
public:	
};

class Effect_ChangeObjectHP : public Effect
{
private:
public:	
};

class Effect_ChangeObjectAttack : public Effect
{
private:
public:	
};

class Effect_StopUnit : public Effect
{
	TASK_OBJECT_H;
};

class 

#endif

