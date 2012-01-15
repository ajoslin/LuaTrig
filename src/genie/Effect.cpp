#include "Effect.h"
#include "util_file.h"
#include "EffectTypes.h"
#include <string.h>

Effect::Effect(long t)
{
	check_value = 0x17;
	unknown = -1;
	type = t;
}

Effect *Effect::createType(long type)
{
	switch(type)
	{
	case EFFECT_None: 
		return new Effect_None(type);
	case EFFECT_ChangeDiplomacy:
		return new Effect_ChangeDiplomacy(type);
	}
}

const char *Effect::getName()
{
	return (type < NUM_EFFECTS) ? types[type] : "Unknown!";
}


void Effect::read(FILE *scx)
{
	//type was read by the trigger, to create the effect
	fread(&type, sizeof(long), 1, scx);
	fread(&check_value, sizeof(long), 1, scx);
	readAiGoal(scx);
	readAmount(scx);
	readResource(scx);
	readDiplomacy(scx);
	readUids(scx);
	readUidLocation(scx);
	readUnitConst(scx);
	readPlayerSource(scx);
	readPlayerTarget(scx);
	readTechnology(scx);
	fread(&stableid, sizeof(long), 1, scx);
	fread(&unknown, sizeof(long), 1, scx);
	readDisplayTime(scx);
	readTriggerIndex(scx);
	readLocation(scx);
	readArea(scx);
	readUnitGroup(scx);
	readUnitType(scx);
	readPanel(scx);
	readText(scx);
	readSound(scx);
	readUids(scx);
}

//this isn't defined in the header because it's too long
void Effect::readUids(FILE *in)
{
	long len;
	fread(&len, sizeof(long), 1, in);
	fskip(in, 4*len);
}

void Effect::write(FILE *scx)
{
	long aigoal=getAiGoal();
	long amount=getAmount();
	long res=getResource();
	long diplo=getDiplomacy();
	std::vector<int> uids=getUids();
	long numselected=uids.size();
	long uid_loc=getUidLocation();
	long uconst=getUnitConst();
	long p_source=getPlayerSource();
	long p_target=getPlayerTarget();
	long tech=getTechnology();
	long disptime=getDisplayTime();
	long trig=getTriggerIndex();
	AOKPT loc=getLocation();
	AOKRECT area=getArea();
	long ugroup=getUnitGroup();
	long utype=getUnitType();
	long panel=getPanel();
	std::string text=getText();
	long textlen=text.size();
	std::string sound=getSound();
	long soundlen=sound.size();

	//these are all longs
	fwrite(&type, sizeof(long), 1, scx);
	fwrite(&check_value, sizeof(long), 1, scx);
	fwrite(&aigoal, sizeof(long), 1, scx);
	fwrite(&amount, sizeof(long), 1, scx);
	fwrite(&res, sizeof(long), 1, scx);
	fwrite(&diplo, sizeof(long), 1, scx);
	fwrite(&numselected, sizeof(long), 1, scx);
	fwrite(&uid_loc, sizeof(long), 1, scx);
	fwrite(&uconst, sizeof(long), 1, scx);
	fwrite(&p_source, sizeof(long), 1, scx);
	fwrite(&p_target, sizeof(long), 1, scx);
	fwrite(&tech, sizeof(long), 1, scx);
	fwrite(&stableid, sizeof(long), 1, scx);
	fwrite(&unknown, sizeof(long), 1, scx);
	fwrite(&disptime, sizeof(long), 1, scx);
	fwrite(&trig, sizeof(long), 1, scx);
	fwrite(&loc.y, sizeof(long), 1, scx);//it's y then x for some reason
	fwrite(&loc.x, sizeof(long), 1, scx);
	fwrite(&area.ll.y, sizeof(long), 1, scx);
	fwrite(&area.ll.x, sizeof(long), 1, scx);
	fwrite(&area.ur.y, sizeof(long), 1, scx);
	fwrite(&area.ur.x, sizeof(long), 1, scx);
	fwrite(&ugroup, sizeof(long), 1, scx);
	fwrite(&utype, sizeof(long), 1, scx);
	fwrite(&panel, sizeof(long), 1, scx);
	fwrite(&textlen, sizeof(long), 1, scx);
	fwrite(text.c_str(), sizeof(char), textlen, scx);
	fwrite(&soundlen, sizeof(long), 1, scx);
	fwrite(sound.c_str(), sizeof(char), soundlen, scx);
	if (numselected>0)
		for (int i=0; i<numselected; i++)
			fwrite(&uids[i], sizeof(long), 1, scx);
}

bool Effect::check()
{
	switch (type)
	{
	case EFFECT_ChangeDiplomacy:
		return (getPlayerSource() >= 0 && getPlayerTarget() >= 0 && getDiplomacy() >= 0);

	case EFFECT_ResearchTechnology:
		return (getPlayerSource() >= 0 && getTechnology() >= 0);

	case EFFECT_SendChat:
		return (getPlayerSource() >= 0 && getText().length()>1);	//AOK missing getText() check

	case EFFECT_PlaySound:
		return (getPlayerSource() >= 0 && getSound().length()>1);	//AOK missing getSound() check

	case EFFECT_SendTribute:
		return (getPlayerSource() >= 0 && getPlayerSource() >= 0 && getResource() >= 0);

	case EFFECT_UnlockGate:
	case EFFECT_LockGate:
		return (getUids().size() >= 0);

	case EFFECT_ActivateTrigger:
	case EFFECT_DeactivateTrigger:
		return (getTriggerIndex() >= 0);

	case EFFECT_AIScriptGoal:
		return (getPlayerSource() >= 0 && getAiGoal() >= 0);

	case EFFECT_CreateObject:
		return (getPlayerSource() >= 0 &&
			getLocation().x >= 0 && getLocation().y >= 0 && getUnitConst()>=0);

	case EFFECT_TaskObject:
	case EFFECT_KillObject:
	case EFFECT_RemoveObject:
	case EFFECT_FreezeUnit:
	case EFFECT_StopUnit:
		return (getUids().size() >= 0 || getArea().ll.x >= 0 || getUnitConst() >= 0);	//AOK missing this

	case EFFECT_DeclareVictory:
		return (getPlayerSource() >= 0);

	//EFFECT_KillObject, EFFECT_RemoveObject above.

	case EFFECT_ChangeView:
		return (getPlayerSource() >= 0 && getLocation().x >= 0 && getLocation().y >= 0);

	case EFFECT_Unload:
		return (getPlayerSource() >= 0
			&& (getUids().size() >= 0 || getArea().ll.x >= 0 || getUnitConst() >= 0)	//AOK missing this
			&& getLocation().x >=0 && getLocation().y >= 0);

	case EFFECT_ChangeOwnership:
		return (getPlayerSource() >= 0 && getPlayerTarget() >= 0
			&& (getUids().size() >= 0 || getArea().ll.x >= 0 || getUnitType() >= 0 || getUnitConst()>=0));	//AOK missing this

	case EFFECT_Patrol:
		return (getUids().size() >= 0 && getLocation().x >= 0 && getLocation().y >= 0);

	case EFFECT_DisplayInstructions:
		return (getPanel() >= 0 && getDisplayTime() >= 0
			&& (getText().length()>1 || stableid));	//AOK missing getText()

	case EFFECT_ClearInstructions:
		return (getPanel() >= 0);

	//EFFECT_FreezeUnit above

	case EFFECT_UseAdvancedButtons:
		return true;	//no properties to set

	case EFFECT_DamageObject:
	case EFFECT_ChangeObjectHP:
	case EFFECT_ChangeObjectAttack:
		return (getAmount() != 0 && getAmount()!=-1		//getAmount() can be negative, cannot be -1
			&& (getUids().size() >= 0 || getArea().ll.x >= 0));	//AOK missing this

	case EFFECT_PlaceFoundation:
		return (getPlayerSource() >= 0 && getUnitConst()>=0
			&& getLocation().x >= 0 && getLocation().y >= 0);

	case EFFECT_ChangeObjectName:
		return (getUids().size() >= 0);	//no getText() check

	//EFFECT_ChangeObjectHP, EFFECT_ChangeObjectAttack, EFFECT_StopUnit above

	//EFFECT_SnapView shares with EFFECT_ChangeView above

	default:
		return false;	//unknown effect type
	}
}


const char *Effect::types[] =
{
	"None",
	"ChangeDiplomacy",
	"ResearchTechnology",
	"SendChat",
	"PlaySound",
	"SendTribute",
	"UnlockGate",
	"LockGate",
	"ActivateTrigger",
	"DeactivateTrigger",
	"AIScriptGoal",
	"CreateObject",
	"TaskObject",
	"DeclareVictory",
	"KillObject",
	"RemoveObject",
	"ChangeView",
	"Unload",
	"ChangeOwnership",
	"Patrol",
	"DisplayInstructions",
	"ClearInstructions",
	"FreezeUnit",
	"UseAdvancedButtons",
	"DamageObject",
	"PlaceFoundation",
	"ChangeObjectName",
	"ChangeObjectHP",
	"ChangeObjectAttack",
	"StopUnit",
};


const char *Effect::propertyTypes[] =
{
	"Amount",
	"Location",
	"Area",
	"AIGoal",
	"Diplomacy",
	"DisplayTime",
	"NumSelected",
	"Panel",
	"PlayerSource",
	"PlayerTarget",
	"Resource",
	"Technology",
	"TriggerIndex",
	"Type",
	"UIDs",
	"UIDLocation",
	"UnitGroup",
	"UnitType",
	"UnitConst",
	"Sound",
	"Text",
};