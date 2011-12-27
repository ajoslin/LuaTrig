#ifndef LTRIGGER_H_
#define LTRIGGER_H_

class Trigger; //fwd here so no need to include
class LEffect;
class LCondition;

class NewTrigger 
{
private:
	Trigger *trig;
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

	Condition *condition(int type) throw(char *);
	Effect *effect(int type) throw(char *);

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

	Effect *effect_None() { return effect(EFFECT_None); };
	Effect *effect_ChangeDiplomacy() { return effect(EFFECT_ChangeDiplomacy); };
	Effect *effect_ResearchTechnology() { return effect(EFFECT_ResearchTechnology); };
	Effect *effect_SendChat() { return effect(EFFECT_SendChat); };
	Effect *effect_PlaySound() { return effect(EFFECT_PlaySound); };
	Effect *effect_SendTribute() { return effect(EFFECT_SendTribute); };
	Effect *effect_UnlockGate() { return effect(EFFECT_UnlockGate); };
	Effect *effect_LockGate() { return effect(EFFECT_LockGate); };
	Effect *effect_ActivateTrigger() { return effect(EFFECT_ActivateTrigger); };
	Effect *effect_DeactivateTrigger() { return effect(EFFECT_DeactivateTrigger); };
	Effect *effect_AIScriptGoal() { return effect(EFFECT_AIScriptGoal); };
	Effect *effect_CreateObject() { return effect(EFFECT_CreateObject); };
	Effect *effect_TaskObject() { return effect(EFFECT_TaskObject); };
	Effect *effect_DeclareVictory() { return effect(EFFECT_DeclareVictory); };
	Effect *effect_KillObject() { return effect(EFFECT_KillObject); };
	Effect *effect_RemoveObject() { return effect(EFFECT_RemoveObject); };
	Effect *effect_ChangeView() { return effect(EFFECT_ChangeView); };
	Effect *effect_Unload() { return effect(EFFECT_Unload); };
	Effect *effect_ChangeOwnership() { return effect(EFFECT_ChangeOwnership); };
	Effect *effect_Patrol() { return effect(EFFECT_Patrol); };
	Effect *effect_DisplayInstructions() { return effect(EFFECT_DisplayInstructions); };
	Effect *effect_ClearInstructions() { return effect(EFFECT_ClearInstructions); };
	Effect *effect_FreezeUnit() { return effect(EFFECT_FreezeUnit); };
	Effect *effect_UseAdvancedButtons() { return effect(EFFECT_UseAdvancedButtons); };
	Effect *effect_DamageObject() { return effect(EFFECT_DamageObject); };
	Effect *effect_PlaceFoundation() { return effect(EFFECT_PlaceFoundation); };
	Effect *effect_ChangeObjectName() { return effect(EFFECT_ChangeObjectName); };
	Effect *effect_ChangeObjectHP() { return effect(EFFECT_ChangeObjectHP); };
	Effect *effect_ChangeObjectAttack() { return effect(EFFECT_ChangeObjectAttack); };
	Effect *effect_StopUnit() { return effect(EFFECT_StopUnit); };
};

#endif