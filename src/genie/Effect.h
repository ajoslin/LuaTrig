#ifndef EFFECT_H_
#define EFFECT_H_

#include <stdio.h>
#include <string>
#include "aok_types.h"

#define MAX_EFFECT 			EFFECT_StopUnit
#define NUM_EFFECTS			30
#define NUM_EFFECT_PARAMS 	21
#define MAX_UNITSEL 		22

enum EffectType
{
	EFFECT_None,
	EFFECT_ChangeDiplomacy,
	EFFECT_ResearchTechnology,
	EFFECT_SendChat,
	EFFECT_PlaySound,
	EFFECT_SendTribute,
	EFFECT_UnlockGate,
	EFFECT_LockGate,
	EFFECT_ActivateTrigger,
	EFFECT_DeactivateTrigger,
	EFFECT_AIScriptGoal,
	EFFECT_CreateObject,
	EFFECT_TaskObject,
	EFFECT_DeclareVictory,
	EFFECT_KillObject,
	EFFECT_RemoveObject,
	EFFECT_ChangeView,
	EFFECT_Unload,
	EFFECT_ChangeOwnership,
	EFFECT_Patrol,
	EFFECT_DisplayInstructions,
	EFFECT_ClearInstructions,
	EFFECT_FreezeUnit,
	EFFECT_UseAdvancedButtons,
	EFFECT_DamageObject,
	EFFECT_PlaceFoundation,
	EFFECT_ChangeObjectName,
	EFFECT_ChangeObjectHP,
	EFFECT_ChangeObjectAttack,
	EFFECT_StopUnit,
};

enum EffectProperty
{
	EFFECTP_Amount,
	EFFECTP_Location,
	EFFECTP_Area,
	EFFECTP_AIGoal,
	EFFECTP_Diplomacy,
	EFFECTP_DisplayTime,
	EFFECTP_NumSelected,
	EFFECTP_Panel,
	EFFECTP_PlayerSource,
	EFFECTP_PlayerTarget,
	EFFECTP_Resource,
	EFFECTP_Technology,
	EFFECTP_TriggerIndex,
	EFFECTP_Type,
	EFFECTP_UIDs,
	EFFECTP_UIDLocation,
	EFFECTP_UnitGroup,
	EFFECTP_UnitType,
	EFFECTP_UnitConst,
	EFFECTP_Sound,
	EFFECTP_Text,
};

class Effect
{
private:
	//miscellaneous value needed by scenario
	long check_value;
	long type;

	//stableid is a misnomer, it's never used anymore except in super old scenarios made by ES. so it can be private in effect
	long stableid;

public:
	Effect(long type);

	const char *getName();

	void read(FILE *in);
	void write(FILE *out);

	bool check();

	virtual long getType() { return type; }

	virtual long getAmount() { return -1; }
	virtual AOKPT getLocation() { return AOKPT(); }
	virtual AOKRECT getArea() { return AOKRECT(); }
	virtual long getAiGoal() { return -1; }
	virtual long getDiplomacy() { return -1; }
	virtual long getDisplayTime() { return -1; }
	virtual long getNumSelected() { return -1; }
	virtual long getPanel() { return -1; }
	virtual long getPlayerSource() { return -1; }
	virtual long getPlayerTarget() { return -1; }
	virtual long getResource() { return -1; }
	virtual long getTriggerIndex() { return -1; }
	virtual long getUid(int i) { return -1; }
	virtual long getUidLocation() { return -1; }
	virtual long getUnitGroup() { return -1; }
	virtual long getUnitType() { return -1; }
	virtual long getUnitConst() { return -1; }
	virtual std::string getSound() { return std::string(); }
	virtual std::string getText() { return std::string(); }	

	static const char *types[NUM_EFFECTS];
	static const char *propertyTypes[NUM_EFFECT_PARAMS];
};

#endif