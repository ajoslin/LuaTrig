#ifndef EFFECT_H_
#define EFFECT_H_

#include "aok_types.h"
#include "util_file.h"
#include <stdio.h>
#include <string>
#include <vector>

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
	
	//always -1
	long unknown;

public:
	Effect(long type);
	static Effect *createType(long type=0);

	const char *getName();

	void read(FILE *in);
	void write(FILE *out);

	bool check();

	virtual long getType() { return type; };

	//getters: return none values by default. inherited classes override these
	virtual long getAmount() { return -1; };
	virtual AOKPT getLocation() { return AOKPT(); };
	virtual AOKRECT getArea() { return AOKRECT(); };
	virtual long getAiGoal() { return -1; };
	virtual long getDiplomacy() { return -1; };
	virtual long getDisplayTime() { return -1; };
	virtual long getNumSelected() { return -1; };
	virtual long getPanel() { return -1; };
	virtual long getPlayerSource() { return -1; };
	virtual long getPlayerTarget() { return -1; };
	virtual long getResource() { return -1; };
	virtual long getTechnology() { return -1; };
	virtual long getTriggerIndex() { return -1; };
	virtual std::vector<int> getUids() { return std::vector<int>(); };
	virtual long getUidLocation() { return -1; };
	virtual long getUnitGroup() { return -1; };
	virtual long getUnitType() { return -1; };
	virtual long getUnitConst() { return -1; };
	virtual std::string getSound() { return std::string(); };
	virtual std::string getText() { return std::string(); };

	//readers: skip scx values by default. inherited classes override these
	//these are not virtual because inherited classes simply override and don't want the above functionality
	void readAmount(FILE *in) { fskip(in, 4); };
	void readLocation(FILE *in) { fskip(in, 8); };
	void readArea(FILE *in) { fskip(in, 16); };
	void readAiGoal(FILE *in) { fskip(in, 4); };
	void readDiplomacy(FILE *in) { fskip(in, 4); };
	void readDisplayTime(FILE *in) { fskip(in, 4); };
	void readNumSelected(FILE *in) { fskip(in, 4); };
	void readPanel(FILE *in) { fskip(in, 4); };
	void readPlayerSource(FILE *in) { fskip(in, 4); };
	void readPlayerTarget(FILE *in) { fskip(in, 4); };
	void readResource(FILE *in) { fskip(in, 4); };
	void readTechnology(FILE *in) { fskip(in, 4); };
	void readTriggerIndex(FILE *in) { fskip(in, 4); };
	void readType(FILE *in) { fskip(in, 4); };
	void readUids(FILE *in); //defined in cpp because it's too long
	void readUidLocation(FILE *in) { fskip(in, 4); };
	void readUnitGroup(FILE *in) { fskip(in, 4); };
	void readUnitType(FILE *in) { fskip(in, 4); };
	void readUnitConst(FILE *in) { fskip(in, 4); };
	void readSound(FILE *in) { readstr(in, std::string()); };
	void readText(FILE *in) { readstr(in, std::string()); };

	static const char *types[NUM_EFFECTS];
	static const char *propertyTypes[NUM_EFFECT_PARAMS];
};

#endif