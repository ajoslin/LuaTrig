#ifndef LTRIGGER_H_
#define LTRIGGER_H_

#include "../genie/Trigger.h"

class LEffect; //fwd so we don't have to include
class LCondition;

class NewTrigger 
{
private:
	Trigger *trig;
	int id;
public:
	NewTrigger(int id) throw(char *);

	void name(const char *name) throw(char *);
	void description(const char *description);
	void on(bool ison);
	void on(int ison);
	void loop(bool isloop);
	void loop(int isloop);
	void objective(bool isobjective);
	void objective(int isobjective);
	void desc_order(int order) throw(char *);

	LCondition *condition(int type) throw(char *);
	LEffect *effect(int type) throw(char *);

	LCondition *condition_None() { return condition(CONDITION_None); };
	LCondition *condition_BringObjectToArea() { return condition(CONDITION_BringObjectToArea); };
	LCondition *condition_BringObjectToObject() { return condition(CONDITION_BringObjectToObject); };
	LCondition *condition_OwnObjects() { return condition(CONDITION_OwnObjects); };
	LCondition *condition_OwnFewerObjects() { return condition(CONDITION_OwnFewerObjects); };
	LCondition *condition_ObjectsInArea() { return condition(CONDITION_ObjectsInArea); };
	LCondition *condition_DestroyObject() { return condition(CONDITION_DestroyObject); };
	LCondition *condition_CaptureObject() { return condition(CONDITION_CaptureObject); };
	LCondition *condition_AccumulateAttribute() { return condition(CONDITION_AccumulateAttribute); };
	LCondition *condition_ResearchTechnology() { return condition(CONDITION_ResearchTechnology); };
	LCondition *condition_Timer() { return condition(CONDITION_Timer); };
	LCondition *condition_ObjectSelected() { return condition(CONDITION_ObjectSelected); };
	LCondition *condition_AISignal() { return condition(CONDITION_AISignal); };
	LCondition *condition_PlayerDefeated() { return condition(CONDITION_PlayerDefeated); };
	LCondition *condition_ObjectHasTarget() { return condition(CONDITION_ObjectHasTarget); };
	LCondition *condition_ObjectVisible() { return condition(CONDITION_ObjectVisible); };
	LCondition *condition_ObjectNotVisible() { return condition(CONDITION_ObjectNotVisible); };
	LCondition *condition_ResearchingTechnology() { return condition(CONDITION_ResearchingTechnology); };
	LCondition *condition_UnitsGarrisoned() { return condition(CONDITION_UnitsGarrisoned); };
	LCondition *condition_DifficultyLevel() { return condition(CONDITION_DifficultyLevel); };

	LEffect *effect_None() { return effect(EFFECT_None); };
	LEffect *effect_ChangeDiplomacy() { return effect(EFFECT_ChangeDiplomacy); };
	LEffect *effect_ResearchTechnology() { return effect(EFFECT_ResearchTechnology); };
	LEffect *effect_SendChat() { return effect(EFFECT_SendChat); };
	LEffect *effect_PlaySound() { return effect(EFFECT_PlaySound); };
	LEffect *effect_SendTribute() { return effect(EFFECT_SendTribute); };
	LEffect *effect_UnlockGate() { return effect(EFFECT_UnlockGate); };
	LEffect *effect_LockGate() { return effect(EFFECT_LockGate); };
	LEffect *effect_ActivateTrigger() { return effect(EFFECT_ActivateTrigger); };
	LEffect *effect_DeactivateTrigger() { return effect(EFFECT_DeactivateTrigger); };
	LEffect *effect_AIScriptGoal() { return effect(EFFECT_AIScriptGoal); };
	LEffect *effect_CreateObject() { return effect(EFFECT_CreateObject); };
	LEffect *effect_TaskObject() { return effect(EFFECT_TaskObject); };
	LEffect *effect_DeclareVictory() { return effect(EFFECT_DeclareVictory); };
	LEffect *effect_KillObject() { return effect(EFFECT_KillObject); };
	LEffect *effect_RemoveObject() { return effect(EFFECT_RemoveObject); };
	LEffect *effect_ChangeView() { return effect(EFFECT_ChangeView); };
	LEffect *effect_Unload() { return effect(EFFECT_Unload); };
	LEffect *effect_ChangeOwnership() { return effect(EFFECT_ChangeOwnership); };
	LEffect *effect_Patrol() { return effect(EFFECT_Patrol); };
	LEffect *effect_DisplayInstructions() { return effect(EFFECT_DisplayInstructions); };
	LEffect *effect_ClearInstructions() { return effect(EFFECT_ClearInstructions); };
	LEffect *effect_FreezeUnit() { return effect(EFFECT_FreezeUnit); };
	LEffect *effect_UseAdvancedButtons() { return effect(EFFECT_UseAdvancedButtons); };
	LEffect *effect_DamageObject() { return effect(EFFECT_DamageObject); };
	LEffect *effect_PlaceFoundation() { return effect(EFFECT_PlaceFoundation); };
	LEffect *effect_ChangeObjectName() { return effect(EFFECT_ChangeObjectName); };
	LEffect *effect_ChangeObjectHP() { return effect(EFFECT_ChangeObjectHP); };
	LEffect *effect_ChangeObjectAttack() { return effect(EFFECT_ChangeObjectAttack); };
	LEffect *effect_StopUnit() { return effect(EFFECT_StopUnit); };
};

#endif