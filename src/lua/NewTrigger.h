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

	LCondition *ConditionNone() { return condition(CONDITION_None); };
	LCondition *ConditionBringObjectToArea() { return condition(CONDITION_BringObjectToArea); };
	LCondition *ConditionBringObjectToObject() { return condition(CONDITION_BringObjectToObject); };
	LCondition *ConditionOwnObjects() { return condition(CONDITION_OwnObjects); };
	LCondition *ConditionOwnFewerObjects() { return condition(CONDITION_OwnFewerObjects); };
	LCondition *ConditionObjectsInArea() { return condition(CONDITION_ObjectsInArea); };
	LCondition *ConditionDestroyObject() { return condition(CONDITION_DestroyObject); };
	LCondition *ConditionCaptureObject() { return condition(CONDITION_CaptureObject); };
	LCondition *ConditionAccumulateAttribute() { return condition(CONDITION_AccumulateAttribute); };
	LCondition *ConditionResearchTechnology() { return condition(CONDITION_ResearchTechnology); };
	LCondition *ConditionTimer() { return condition(CONDITION_Timer); };
	LCondition *ConditionObjectSelected() { return condition(CONDITION_ObjectSelected); };
	LCondition *ConditionAISignal() { return condition(CONDITION_AISignal); };
	LCondition *ConditionPlayerDefeated() { return condition(CONDITION_PlayerDefeated); };
	LCondition *ConditionObjectHasTarget() { return condition(CONDITION_ObjectHasTarget); };
	LCondition *ConditionObjectVisible() { return condition(CONDITION_ObjectVisible); };
	LCondition *ConditionObjectNotVisible() { return condition(CONDITION_ObjectNotVisible); };
	LCondition *ConditionResearchingTechnology() { return condition(CONDITION_ResearchingTechnology); };
	LCondition *ConditionUnitsGarrisoned() { return condition(CONDITION_UnitsGarrisoned); };
	LCondition *ConditionDifficultyLevel() { return condition(CONDITION_DifficultyLevel); };

	LEffect *EffectNone() { return effect(EFFECT_None); };
	LEffect *EffectChangeDiplomacy() { return effect(EFFECT_ChangeDiplomacy); };
	LEffect *EffectResearchTechnology() { return effect(EFFECT_ResearchTechnology); };
	LEffect *EffectSendChat() { return effect(EFFECT_SendChat); };
	LEffect *EffectPlaySound() { return effect(EFFECT_PlaySound); };
	LEffect *EffectSendTribute() { return effect(EFFECT_SendTribute); };
	LEffect *EffectUnlockGate() { return effect(EFFECT_UnlockGate); };
	LEffect *EffectLockGate() { return effect(EFFECT_LockGate); };
	LEffect *EffectActivateTrigger() { return effect(EFFECT_ActivateTrigger); };
	LEffect *EffectDeactivateTrigger() { return effect(EFFECT_DeactivateTrigger); };
	LEffect *EffectAIScriptGoal() { return effect(EFFECT_AIScriptGoal); };
	LEffect *EffectCreateObject() { return effect(EFFECT_CreateObject); };
	LEffect *EffectTaskObject() { return effect(EFFECT_TaskObject); };
	LEffect *EffectDeclareVictory() { return effect(EFFECT_DeclareVictory); };
	LEffect *EffectKillObject() { return effect(EFFECT_KillObject); };
	LEffect *EffectRemoveObject() { return effect(EFFECT_RemoveObject); };
	LEffect *EffectChangeView() { return effect(EFFECT_ChangeView); };
	LEffect *EffectUnload() { return effect(EFFECT_Unload); };
	LEffect *EffectChangeOwnership() { return effect(EFFECT_ChangeOwnership); };
	LEffect *EffectPatrol() { return effect(EFFECT_Patrol); };
	LEffect *EffectDisplayInstructions() { return effect(EFFECT_DisplayInstructions); };
	LEffect *EffectClearInstructions() { return effect(EFFECT_ClearInstructions); };
	LEffect *EffectFreezeUnit() { return effect(EFFECT_FreezeUnit); };
	LEffect *EffectUseAdvancedButtons() { return effect(EFFECT_UseAdvancedButtons); };
	LEffect *EffectDamageObject() { return effect(EFFECT_DamageObject); };
	LEffect *EffectPlaceFoundation() { return effect(EFFECT_PlaceFoundation); };
	LEffect *EffectChangeObjectName() { return effect(EFFECT_ChangeObjectName); };
	LEffect *EffectChangeObjectHP() { return effect(EFFECT_ChangeObjectHP); };
	LEffect *EffectChangeObjectAttack() { return effect(EFFECT_ChangeObjectAttack); };
	LEffect *EffectStopUnit() { return effect(EFFECT_StopUnit); };
};

#endif