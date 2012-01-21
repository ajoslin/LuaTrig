#include "NewTrigger.h"
#include "LuaFile.h"
#include <algorithm>
#include <string.h>

NewTrigger::NewTrigger(int id) throw(char *)
{
	if (id==-1) //if not given an id, get next automatically
		id=LuaFile::current()->triggers.size();
	
	this->id = id;
	trig = new Trigger;
	if (!LuaFile::current()->add_trigger(trig, id))
	{
		char *err = new char[75];
		sprintf(err, "Error in trigger %d. Could not create trigger, given ID %d. Expected ID consecutive to that of previous trigger and nonnegative.", id, id);
		throw(err);
		delete this;
	}
}

NewTrigger::NewTrigger() throw(char *)
{
	NewTrigger(-1);
}

void NewTrigger::name(const char *name) throw(char *)
{
	if (strlen(name)>=trig->MAX_TRIGNAME)
	{
		char *err = new char[75];
		sprintf(err, "Error in trigger %d: Could not assign name given. Exceeds maximum name length of %d.", id, trig->MAX_TRIGNAME);
		throw(err);	
	}
	else
	{
		trig->name.resize(strlen(name)+1);
		trig->name.assign(name);
		trig->name+='\0';
	}
}

void NewTrigger::description(const char *description)
{
	trig->description.resize(strlen(description)+1);
	trig->description.assign(description);
	trig->description+='\0';
}

void NewTrigger::on(bool ison)
{
	trig->state=ison;
}
void NewTrigger::on(int ison)
{
	on(ison==0 ? false : true);
}

void NewTrigger::loop(bool isloop)
{
	trig->loop=(isloop==false ? 0 : 1);
}
void NewTrigger::loop(int isloop)
{
	loop(isloop==0 ? false : true);
}

void NewTrigger::objective(bool isobjective)
{
	trig->obj=(isobjective==true ? 1 : 0);
}
void NewTrigger::objective(int isobjective)
{
	objective(isobjective==0 ? false : true);
}

void NewTrigger::desc_order(int order)
{
	trig->obj_order=std::max(-1, order);
}


Condition_None * NewTrigger::ConditionNone() { 
	Condition_None *c= new Condition_None();
	trig->conds.push_back(c);
	return c;
}
Condition_BringObjectToArea * NewTrigger::ConditionBringObjectToArea() { 
	Condition_BringObjectToArea *c= new Condition_BringObjectToArea();
	trig->conds.push_back(c);
	return c;
}
Condition_BringObjectToObject * NewTrigger::ConditionBringObjectToObject() { 
	Condition_BringObjectToObject *c= new Condition_BringObjectToObject();
	trig->conds.push_back(c);
	return c;
}
Condition_OwnObjects * NewTrigger::ConditionOwnObjects() { 
	Condition_OwnObjects *c= new Condition_OwnObjects();
	trig->conds.push_back(c);
	return c;
}
Condition_OwnFewerObjects * NewTrigger::ConditionOwnFewerObjects() { 
	Condition_OwnFewerObjects *c= new Condition_OwnFewerObjects();
	trig->conds.push_back(c);
	return c;
}
Condition_ObjectsInArea * NewTrigger::ConditionObjectsInArea() { 
	Condition_ObjectsInArea *c= new Condition_ObjectsInArea();
	trig->conds.push_back(c);
	return c;
}
Condition_DestroyObject * NewTrigger::ConditionDestroyObject() { 
	Condition_DestroyObject *c= new Condition_DestroyObject();
	trig->conds.push_back(c);
	return c;
}
Condition_CaptureObject * NewTrigger::ConditionCaptureObject() { 
	Condition_CaptureObject *c= new Condition_CaptureObject();
	trig->conds.push_back(c);
	return c;
}
Condition_AccumulateAttribute * NewTrigger::ConditionAccumulateAttribute() { 
	Condition_AccumulateAttribute *c= new Condition_AccumulateAttribute();
	trig->conds.push_back(c);
	return c;
}
Condition_ResearchTechnology * NewTrigger::ConditionResearchTechnology() { 
	Condition_ResearchTechnology *c= new Condition_ResearchTechnology();
	trig->conds.push_back(c);
	return c;
}
Condition_Timer * NewTrigger::ConditionTimer() { 
	Condition_Timer *c= new Condition_Timer();
	trig->conds.push_back(c);
	return c;
}
Condition_ObjectSelected * NewTrigger::ConditionObjectSelected() { 
	Condition_ObjectSelected *c= new Condition_ObjectSelected();
	trig->conds.push_back(c);
	return c;
}
Condition_AISignal * NewTrigger::ConditionAiSignal() { 
	Condition_AISignal *c= new Condition_AISignal();
	trig->conds.push_back(c);
	return c;
}
Condition_PlayerDefeated * NewTrigger::ConditionPlayerDefeated() { 
	Condition_PlayerDefeated *c= new Condition_PlayerDefeated();
	trig->conds.push_back(c);
	return c;
}
Condition_ObjectHasTarget * NewTrigger::ConditionObjectHasTarget() { 
	Condition_ObjectHasTarget *c= new Condition_ObjectHasTarget();
	trig->conds.push_back(c);
	return c;
}
Condition_ObjectVisible * NewTrigger::ConditionObjectVisible() { 
	Condition_ObjectVisible *c= new Condition_ObjectVisible();
	trig->conds.push_back(c);
	return c;
}
Condition_ObjectNotVisible * NewTrigger::ConditionObjectNotVisible() { 
	Condition_ObjectNotVisible *c= new Condition_ObjectNotVisible();
	trig->conds.push_back(c);
	return c;
}
Condition_ResearchingTechnology * NewTrigger::ConditionResearchingTechnology() { 
	Condition_ResearchingTechnology *c= new Condition_ResearchingTechnology();
	trig->conds.push_back(c);
	return c;
}
Condition_UnitsGarrisoned * NewTrigger::ConditionUnitsGarrisoned() { 
	Condition_UnitsGarrisoned *c= new Condition_UnitsGarrisoned();
	trig->conds.push_back(c);
	return c;
}
Condition_DifficultyLevel * NewTrigger::ConditionDifficultyLevel() { 
	Condition_DifficultyLevel *c= new Condition_DifficultyLevel();
	trig->conds.push_back(c);
	return c;
}

Effect_None * NewTrigger::EffectNone() { 
	Effect_None * e = new Effect_None();
	trig->effects.push_back(e);
	return e;
}
Effect_ChangeDiplomacy * NewTrigger::EffectChangeDiplomacy() { 
	Effect_ChangeDiplomacy * e = new Effect_ChangeDiplomacy();
	trig->effects.push_back(e);
	return e;
}
Effect_ResearchTechnology * NewTrigger::EffectResearchTechnology() { 
	Effect_ResearchTechnology * e = new Effect_ResearchTechnology();
	trig->effects.push_back(e);
	return e;
}
Effect_SendChat * NewTrigger::EffectSendChat() { 
	Effect_SendChat * e = new Effect_SendChat();
	trig->effects.push_back(e);
	return e;
}
Effect_PlaySound * NewTrigger::EffectPlaySound() { 
	Effect_PlaySound * e = new Effect_PlaySound();
	trig->effects.push_back(e);
	return e;
}
Effect_SendTribute * NewTrigger::EffectSendTribute() { 
	Effect_SendTribute * e = new Effect_SendTribute();
	trig->effects.push_back(e);
	return e;
}
Effect_UnlockGate * NewTrigger::EffectUnlockGate() { 
	Effect_UnlockGate * e = new Effect_UnlockGate();
	trig->effects.push_back(e);
	return e;
}
Effect_LockGate * NewTrigger::EffectLockGate() { 
	Effect_LockGate * e = new Effect_LockGate();
	trig->effects.push_back(e);
	return e;
}
Effect_ActivateTrigger * NewTrigger::EffectActivateTrigger() { 
	Effect_ActivateTrigger * e = new Effect_ActivateTrigger();
	trig->effects.push_back(e);
	return e;
}
Effect_DeactivateTrigger * NewTrigger::EffectDeactivateTrigger() { 
	Effect_DeactivateTrigger * e = new Effect_DeactivateTrigger();
	trig->effects.push_back(e);
	return e;
}
Effect_AIScriptGoal * NewTrigger::EffectAIScriptGoal() { 
	Effect_AIScriptGoal * e = new Effect_AIScriptGoal();
	trig->effects.push_back(e);
	return e;
}
Effect_CreateObject * NewTrigger::EffectCreateObject() { 
	Effect_CreateObject * e = new Effect_CreateObject();
	trig->effects.push_back(e);
	return e;
}
Effect_TaskObject * NewTrigger::EffectTaskObject() { 
	Effect_TaskObject * e = new Effect_TaskObject();
	trig->effects.push_back(e);
	return e;
}
Effect_DeclareVictory * NewTrigger::EffectDeclareVictory() { 
	Effect_DeclareVictory * e = new Effect_DeclareVictory();
	trig->effects.push_back(e);
	return e;
}
Effect_KillObject * NewTrigger::EffectKillObject() { 
	Effect_KillObject * e = new Effect_KillObject();
	trig->effects.push_back(e);
	return e;
}
Effect_RemoveObject * NewTrigger::EffectRemoveObject() { 
	Effect_RemoveObject * e = new Effect_RemoveObject();
	trig->effects.push_back(e);
	return e;
}
Effect_ChangeView * NewTrigger::EffectChangeView() { 
	Effect_ChangeView * e = new Effect_ChangeView();
	trig->effects.push_back(e);
	return e;
}
Effect_Unload * NewTrigger::EffectUnload() { 
	Effect_Unload * e = new Effect_Unload();
	trig->effects.push_back(e);
	return e;
}
Effect_ChangeOwnership * NewTrigger::EffectChangeOwnership() { 
	Effect_ChangeOwnership * e = new Effect_ChangeOwnership();
	trig->effects.push_back(e);
	return e;
}
Effect_Patrol * NewTrigger::EffectPatrol() { 
	Effect_Patrol * e = new Effect_Patrol();
	trig->effects.push_back(e);
	return e;
}
Effect_DisplayInstructions * NewTrigger::EffectDisplayInstructions() { 
	Effect_DisplayInstructions * e = new Effect_DisplayInstructions();
	trig->effects.push_back(e);
	return e;
}
Effect_ClearInstructions * NewTrigger::EffectClearInstructions() { 
	Effect_ClearInstructions * e = new Effect_ClearInstructions();
	trig->effects.push_back(e);
	return e;
}
Effect_FreezeUnit * NewTrigger::EffectFreezeUnit() { 
	Effect_FreezeUnit * e = new Effect_FreezeUnit();
	trig->effects.push_back(e);
	return e;
}
Effect_UseAdvancedButtons * NewTrigger::EffectUseAdvancedButtons() { 
	Effect_UseAdvancedButtons * e = new Effect_UseAdvancedButtons();
	trig->effects.push_back(e);
	return e;
}
Effect_DamageObject * NewTrigger::EffectDamageObject() { 
	Effect_DamageObject * e = new Effect_DamageObject();
	trig->effects.push_back(e);
	return e;
}
Effect_PlaceFoundation * NewTrigger::EffectPlaceFoundation() { 
	Effect_PlaceFoundation * e = new Effect_PlaceFoundation();
	trig->effects.push_back(e);
	return e;
}
Effect_ChangeObjectName * NewTrigger::EffectChangeObjectName() { 
	Effect_ChangeObjectName * e = new Effect_ChangeObjectName();
	trig->effects.push_back(e);
	return e;
}
Effect_ChangeObjectHP * NewTrigger::EffectChangeObjectHP() { 
	Effect_ChangeObjectHP * e = new Effect_ChangeObjectHP();
	trig->effects.push_back(e);
	return e;
}
Effect_ChangeObjectAttack * NewTrigger::EffectChangeObjectAttack() { 
	Effect_ChangeObjectAttack * e = new Effect_ChangeObjectAttack();
	trig->effects.push_back(e);
	return e;
}
Effect_StopUnit * NewTrigger::EffectStopUnit() { 
	Effect_StopUnit * e = new Effect_StopUnit();
	trig->effects.push_back(e);
	return e;
}
