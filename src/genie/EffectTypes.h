#ifndef EFFECT_TYPES_H_
#define EFFECT_TYPES_H_

#include "Effect.h"
#include "ECTypes.h"
#include <string>
#include <vector>

class Effect_None : public Effect
{
	public:
		Effect_None() : Effect(EFFECT_None) {};
};

class Effect_ChangeDiplomacy : public Effect
{
private:
	PSOURCE_H_FIELD;
	PTARGET_H_FIELD;
	DIPLO_H_FIELD;
public:	
	Effect_ChangeDiplomacy() : Effect(EFFECT_ChangeDiplomacy) {};
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
	Effect_ResearchTechnology() : Effect(EFFECT_ResearchTechnology) {};
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
	Effect_SendChat() : Effect(EFFECT_SendChat) {};
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
	Effect_PlaySound() : Effect(EFFECT_PlaySound) {};
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
	Effect_SendTribute() : Effect(EFFECT_SendTribute) {};
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
	Effect_UnlockGate() : Effect(EFFECT_UnlockGate) {};
	UIDS_H_FUNC;	
};

class Effect_LockGate : public Effect
{
private:
	UIDS_H_FIELD;
public:	
	Effect_LockGate() : Effect(EFFECT_LockGate) {};
	UIDS_H_FUNC;
};

class Effect_ActivateTrigger : public Effect
{
private:
	TRIGGER_H_FIELD;
public:	
	Effect_ActivateTrigger() : Effect(EFFECT_ActivateTrigger) {};
	TRIGGER_H_FUNC;
};

class Effect_DeactivateTrigger : public Effect
{
private:
	TRIGGER_H_FIELD;
public:	
	Effect_DeactivateTrigger() : Effect(EFFECT_DeactivateTrigger) {};
	TRIGGER_H_FUNC;
};

class Effect_AIScriptGoal : public Effect
{
private:
	AIGOAL_H_FIELD;
	PSOURCE_H_FIELD;
public:	
	Effect_AIScriptGoal() : Effect(EFFECT_AIScriptGoal) {};
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
	Effect_CreateObject() : Effect(EFFECT_CreateObject) {};
	PSOURCE_H_FUNC;
	UCONST_H_FUNC;
	LOCATION_H_FUNC;
};

#define TASK_OBJECT_H_FIELDS \
	PSOURCE_H_FIELD; \
	UIDS_H_FIELD; \
	UIDLOC_H_FIELD; \
	LOCATION_H_FIELD; \
	AREA_H_FIELD; \
	UGROUP_H_FIELD; \
	UTYPE_H_FIELD; \
	UCONST_H_FIELD
#define TASK_OBJECT_H_FUNCS \
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
private:
	TASK_OBJECT_H_FIELDS;
public:
	Effect_TaskObject() : Effect(EFFECT_TaskObject) {};
	TASK_OBJECT_H_FUNCS;
};

class Effect_DeclareVictory : public Effect
{
private:
	PSOURCE_H_FIELD;
public:	
	Effect_DeclareVictory() : Effect(EFFECT_DeclareVictory) {};
	PSOURCE_H_FUNC;
};

class Effect_KillObject : public Effect
{
private:
	TASK_OBJECT_H_FIELDS;
public:
	Effect_KillObject() : Effect(EFFECT_KillObject) {};
	TASK_OBJECT_H_FUNCS;
};

class Effect_RemoveObject : public Effect
{
private:
	TASK_OBJECT_H_FIELDS;
public:
	Effect_RemoveObject() : Effect(EFFECT_RemoveObject) {};
	TASK_OBJECT_H_FUNCS;
};

class Effect_ChangeView : public Effect
{
private:
	PSOURCE_H_FIELD;
	LOCATION_H_FIELD;
public:	
	Effect_ChangeView() : Effect(EFFECT_ChangeView) {};
	PSOURCE_H_FUNC;
	LOCATION_H_FUNC;
};

class Effect_Unload : public Effect
{
private:
	TASK_OBJECT_H_FIELDS;
public:
	Effect_Unload() : Effect(EFFECT_Unload) {};
	TASK_OBJECT_H_FUNCS;
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
	Effect_ChangeOwnership() : Effect(EFFECT_ChangeOwnership) {};
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
	Effect_Patrol() : Effect(EFFECT_Patrol) {};
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
	Effect_DisplayInstructions() : Effect(EFFECT_DisplayInstructions) {};
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
	Effect_ClearInstructions() : Effect(EFFECT_ClearInstructions) {};
	PANEL_H_FUNC;
};

class Effect_FreezeUnit : public Effect
{
private:
	TASK_OBJECT_H_FIELDS;
public:
	Effect_FreezeUnit() : Effect(EFFECT_FreezeUnit) {};
	TASK_OBJECT_H_FUNCS;
};

class Effect_UseAdvancedButtons : public Effect
{
public:
	Effect_UseAdvancedButtons() : Effect(EFFECT_UseAdvancedButtons) {};
};

#define DAMAGE_OBJECT_H_FIELDS \
	PSOURCE_H_FIELD; \
	AREA_H_FIELD; \
	UIDS_H_FIELD; \
	AMOUNT_H_FIELD; \
	UGROUP_H_FIELD; \
	UCONST_H_FIELD; \
	UTYPE_H_FIELD
#define DAMAGE_OBJECT_H_FUNCS \
	PSOURCE_H_FUNC; \
	AREA_H_FUNC; \
	UIDS_H_FUNC; \
	AMOUNT_H_FUNC; \
	UGROUP_H_FUNC; \
	UCONST_H_FUNC; \
	UTYPE_H_FUNC

	

class Effect_DamageObject : public Effect
{
private:
	DAMAGE_OBJECT_H_FIELDS;
public:
	Effect_DamageObject() : Effect(EFFECT_DamageObject) {};
	DAMAGE_OBJECT_H_FUNCS;
};

class Effect_PlaceFoundation : public Effect
{
private:
	PSOURCE_H_FIELD;
	LOCATION_H_FIELD;
	UCONST_H_FIELD;
public:
	Effect_PlaceFoundation() : Effect(EFFECT_PlaceFoundation) {};
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
	Effect_ChangeObjectName() : Effect(EFFECT_ChangeObjectName) {};
	UIDS_H_FUNC;
	TEXT_H_FUNC;
};

class Effect_ChangeObjectHP : public Effect
{
private:
	DAMAGE_OBJECT_H_FIELDS;
public:
	Effect_ChangeObjectHP() : Effect(EFFECT_ChangeObjectHP) {};
	DAMAGE_OBJECT_H_FUNCS;
};

class Effect_ChangeObjectAttack : public Effect
{
private:
	DAMAGE_OBJECT_H_FIELDS;
public:
	Effect_ChangeObjectAttack() : Effect(EFFECT_ChangeObjectAttack) {};
	DAMAGE_OBJECT_H_FUNCS;
};

class Effect_StopUnit : public Effect
{
private:
	TASK_OBJECT_H_FIELDS;
public:
	Effect_StopUnit() : Effect(EFFECT_StopUnit) {};
	TASK_OBJECT_H_FUNCS;
};


#endif



