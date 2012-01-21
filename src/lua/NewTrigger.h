#ifndef LTRIGGER_H_
#define LTRIGGER_H_

//Wrapper for triggers in lua

#include "../genie/Trigger.h"
#include "../genie/EffectTypes.h"
#include "../genie/ConditionTypes.h"

class NewTrigger 
{
private:
	Trigger *trig;
	int id;
	
public:
	NewTrigger(int id) throw(char *);
	NewTrigger() throw(char *);

	void name(const char *name) throw(char *);
	void description(const char *description);
	void on(bool ison);
	void on(int ison);
	void loop(bool isloop);
	void loop(int isloop);
	void objective(bool isobjective);
	void objective(int isobjective);
	void desc_order(int order);

	Condition_None * ConditionNone();
	Condition_BringObjectToArea * ConditionBringObjectToArea();
	Condition_BringObjectToObject * ConditionBringObjectToObject();
	Condition_OwnObjects * ConditionOwnObjects();
	Condition_OwnFewerObjects * ConditionOwnFewerObjects();
	Condition_ObjectsInArea * ConditionObjectsInArea();
	Condition_DestroyObject * ConditionDestroyObject();
	Condition_CaptureObject * ConditionCaptureObject();
	Condition_AccumulateAttribute * ConditionAccumulateAttribute();
	Condition_ResearchTechnology * ConditionResearchTechnology();
	Condition_Timer * ConditionTimer();
	Condition_ObjectSelected * ConditionObjectSelected();
	Condition_AISignal * ConditionAiSignal();
	Condition_PlayerDefeated * ConditionPlayerDefeated();
	Condition_ObjectHasTarget * ConditionObjectHasTarget();
	Condition_ObjectVisible * ConditionObjectVisible();
	Condition_ObjectNotVisible * ConditionObjectNotVisible();
	Condition_ResearchingTechnology * ConditionResearchingTechnology();
	Condition_UnitsGarrisoned * ConditionUnitsGarrisoned();
	Condition_DifficultyLevel * ConditionDifficultyLevel();

	Effect_None * EffectNone();
	Effect_ChangeDiplomacy * EffectChangeDiplomacy();
	Effect_ResearchTechnology * EffectResearchTechnology();
	Effect_SendChat * EffectSendChat();
	Effect_PlaySound * EffectPlaySound();
	Effect_SendTribute * EffectSendTribute();
	Effect_UnlockGate * EffectUnlockGate();
	Effect_LockGate * EffectLockGate();
	Effect_ActivateTrigger * EffectActivateTrigger();
	Effect_DeactivateTrigger * EffectDeactivateTrigger();
	Effect_AIScriptGoal * EffectAIScriptGoal();
	Effect_CreateObject * EffectCreateObject();
	Effect_TaskObject * EffectTaskObject();
	Effect_DeclareVictory * EffectDeclareVictory();
	Effect_KillObject * EffectKillObject();
	Effect_RemoveObject * EffectRemoveObject();
	Effect_ChangeView * EffectChangeView();
	Effect_Unload * EffectUnload();
	Effect_ChangeOwnership * EffectChangeOwnership();
	Effect_Patrol * EffectPatrol();
	Effect_DisplayInstructions * EffectDisplayInstructions();
	Effect_ClearInstructions * EffectClearInstructions();
	Effect_FreezeUnit * EffectFreezeUnit();
	Effect_UseAdvancedButtons * EffectUseAdvancedButtons();
	Effect_DamageObject * EffectDamageObject();
	Effect_PlaceFoundation * EffectPlaceFoundation();
	Effect_ChangeObjectName * EffectChangeObjectName();
	Effect_ChangeObjectHP * EffectChangeObjectHP();
	Effect_ChangeObjectAttack * EffectChangeObjectAttack();
	Effect_StopUnit * EffectStopUnit();
};

#endif


