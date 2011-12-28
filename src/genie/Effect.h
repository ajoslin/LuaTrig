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
public:
	Effect();

	const char *getName();

	void read(FILE *in);
	void write(FILE *out);

	bool check();
	bool valid_property(EffectProperty);

	AOKPT location;
	AOKRECT area;
	long ai_goal;
	long amount;
	long check_value;
	long diplomacy;
	long display_time;
	long num_selected;
	long panel;
	long player_source;
	long player_target;
	long resource;
	long stableid;         // string table for text
	long technology;
	long trigger_index;
	long type;
	long uids[MAX_UNITSEL];		//array of selected units
	long uid_location;
	long unit_group;
	long unit_type;
	long unit_const;
	long unknown;

	std::string text;
	std::string sound;

	static const char* types[NUM_EFFECTS];
	static const char* partypes[NUM_EFFECT_PARAMS];
};

#endif