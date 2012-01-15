#ifndef EFFECT_TYPES_H_
#define EFFECT_TYPES_H_

#include "Effect.h"
#include "ECTypes.h"
#include <string>
#include <vector>

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
	PSOURCE_H_FUNC;
	PTARGET_H_FUNC;
	DIPLO_H_FUNC;
};

class Effect_ResearchTechnology : public Effect
{
private:
	PSOURCE_H_FIELD;
	TECH_H_FIELD;
public:	
	PSOURCE_H_FUNC;
	TECH_H_FUNC;
};

class Effect_SendChat : public Effect
{
private:
	PSOURCE_H_FIELD;
	TEXT_H_FIELD;
	SOUND_H_FIELD;
public:	
	PSOURCE_H_FUNC;
	TEXT_H_FUNC;
	SOUND_H_FUNC;
};

class Effect_PlaySound : public Effect
{
private:
	PSOURCE_H_FIELD;
	SOUND_H_FIELD;
public:	
	PSOURCE_H_FUNC;
	SOUND_H_FUNC;
};

class Effect_SendTribute : public Effect
{
private:
	PSOURCE_H_FIELD;
	PTARGET_H_FIELD;
	RESOURCE_H_FIELD;
	AMOUNT_H_FIELD;
public:	
	PSOURCE_H_FUNC;
	PTARGET_H_FUNC;
	RESOURCE_H_FUNC;
	AMOUNT_H_FUNC;
};

class Effect_UnlockGate : public Effect
{
private:
	UIDS_H_FIELD;
public:	
	UIDS_H_FUNC;	
};

class Effect_LockGate : public Effect
{
private:
	UIDS_H_FIELD;
public:	
	UIDS_H_FUNC;
};

class Effect_ActivateTrigger : public Effect
{
private:
	TRIGGER_H_FIELD;
public:	
	TRIGGER_H_FUNC;
};

class Effect_DeactivateTrigger : public Effect
{
private:
	TRIGGER_H_FIELD;
public:	
	TRIGGER_H_FUNC;
};

class Effect_AIScriptGoal : public Effect
{
private:
	AIGOAL_H_FIELD;
	PSOURCE_H_FIELD;
public:	
	PSOURCE_H_FUNC;
	AIGOAL_H_FUNC;
};

class Effect_CreateObject : public Effect
{
private:
	UCONST_H_FIELD;
	LOCATION_H_FIELD;
	PSOURCE_H_FIELD;
public:	
	PSOURCE_H_FUNC;
	UCONST_H_FUNC;
	LOCATION_H_FUNC;
};

#define TASK_OBJECT_H \
private: \
	PSOURCE_H_FIELD; \
	UIDS_H_FIELD; \
	UIDLOC_H_FIELD; \
	LOCATION_H_FIELD; \
	AREA_H_FIELD; \
	UGROUP_H_FIELD; \
	UTYPE_H_FIELD; \
	UCONST_H_FIELD; \
public:	 \
	PSOURCE_H_FUNC; \
	UIDS_H_FUNC; \
	UIDLOC_H_FUNC; \
	LOCATION_H_FUNC; \
	AREA_H_FUNC; \
	UGROUP_H_FUNC; \
	UTYPE_H_FUNC; \
	UCONST_H_FUNC

class Effect_TaskObject : public Effect
{
	TASK_OBJECT_H;
};

class Effect_DeclareVictory : public Effect
{
private:
	PSOURCE_H_FIELD;
public:	
	PSOURCE_H_FUNC;
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
	PSOURCE_H_FIELD;
	LOCATION_H_FIELD;
public:	
	PSOURCE_H_FUNC;
	LOCATION_H_FUNC;
};

class Effect_Unload : public Effect
{
	TASK_OBJECT_H;
};

class Effect_ChangeOwnership : public Effect
{
private:
	PSOURCE_H_FIELD;
	PTARGET_H_FIELD;
	AREA_H_FIELD;
	UIDS_H_FIELD;
	UCONST_H_FIELD;
	UTYPE_H_FIELD;
	UGROUP_H_FIELD;
public:	
	PSOURCE_H_FUNC;
	PTARGET_H_FUNC;
	AREA_H_FUNC;
	UIDS_H_FUNC;
	UCONST_H_FUNC;
	UTYPE_H_FUNC;
	UGROUP_H_FUNC;
};

class Effect_Patrol : public Effect
{
private:
	LOCATION_H_FIELD;
	UIDS_H_FIELD;
public:	
	LOCATION_H_FUNC;
	UIDS_H_FUNC;
};

class Effect_DisplayInstructions : public Effect
{
private:
	PANEL_H_FIELD;
	DISPTIME_H_FIELD;
	TEXT_H_FIELD;
	SOUND_H_FIELD;
public:	
	PANEL_H_FUNC;
	DISPTIME_H_FUNC;
	TEXT_H_FUNC;
	SOUND_H_FUNC;
};

class Effect_ClearInstructions : public Effect
{
private:
	PANEL_H_FIELD;
public:	
	PANEL_H_FUNC;
};

class Effect_FreezeUnit : public Effect
{
	TASK_OBJECT_H;
};

class Effect_UseAdvancedButtons : public Effect
{
};

#define DAMAGE_OBJECT_H \
private: \
	PSOURCE_H_FIELD; \
	AREA_H_FIELD; \
	UIDS_H_FIELD; \
	AMOUNT_H_FIELD; \
	UGROUP_H_FIELD; \
	UCONST_H_FIELD; \
	UTYPE_H_FIELD; \
public: \
	PSOURCE_H_FUNC; \
	AREA_H_FUNC; \
	UIDS_H_FUNC; \
	AMOUNT_H_FUNC; \
	UGROUP_H_FUNC; \
	UCONST_H_FUNC; \
	UTYPE_H_FUNC

	

class Effect_DamageObject : public Effect
{
	DAMAGE_OBJECT_H;
};

class Effect_PlaceFoundation : public Effect
{
private:
	PSOURCE_H_FIELD;
	LOCATION_H_FIELD;
	UCONST_H_FIELD;
public:
	PSOURCE_H_FUNC;
	LOCATION_H_FUNC;
	UCONST_H_FUNC;
};

class Effect_ChangeObjectName : public Effect
{
private:
	UIDS_H_FIELD;
	TEXT_H_FIELD;
public:	
	UIDS_H_FUNC;
	TEXT_H_FUNC;
};

class Effect_ChangeObjectHP : public Effect
{
	DAMAGE_OBJECT_H;
};

class Effect_ChangeObjectAttack : public Effect
{
	DAMAGE_OBJECT_H;
};

class Effect_StopUnit : public Effect
{
	TASK_OBJECT_H;
};

class 

#endif

