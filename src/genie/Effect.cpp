#include "Effect.h"
#include <string.h>

Effect::Effect(long t)
{
	check_value=0x17;
	type=t;
}

const char *Effect::getName()
{
	return (type < NUM_EFFECTS) ? types[type] : "Unknown!";
}


void Effect::read(FILE *scx)
{
	//these are all longs
	fread(&type, sizeof(long), 1, scx);
	fread(&check_value, sizeof(long), 1, scx);
	fread(&ai_goal, sizeof(long), 1, scx);
	fread(&amount, sizeof(long), 1, scx);
	fread(&resource, sizeof(long), 1, scx);
	fread(&diplomacy, sizeof(long), 1, scx);
	fread(&num_selected, sizeof(long), 1, scx);
	fread(&uid_location, sizeof(long), 1, scx);
	fread(&unit_const, sizeof(long), 1, scx);
	fread(&player_source, sizeof(long), 1, scx);
	fread(&player_target, sizeof(long), 1, scx);
	fread(&technology, sizeof(long), 1, scx);
	fread(&stableid, sizeof(long), 1, scx);
	fread(&unknown, sizeof(long), 1, scx);
	fread(&display_time, sizeof(long), 1, scx);
	fread(&trigger_index, sizeof(long), 1, scx);

	//it's y then x for some reason
	fread(&location.y, sizeof(long), 1, scx);
	fread(&location.x, sizeof(long), 1, scx);
	fread(&area.ur.y, sizeof(long), 1, scx);
	fread(&area.ur.x, sizeof(long), 1, scx);
	fread(&area.ll.y, sizeof(long), 1, scx);
	fread(&area.ll.x, sizeof(long), 1, scx);

	fread(&unit_group, sizeof(long), 1, scx);
	fread(&unit_type, sizeof(long), 1, scx);
	fread(&panel, sizeof(long), 1, scx);

	long textlen;
	fread(&textlen, sizeof(long), 1, scx);

	char c;

	text.resize(textlen);
	for (int i=0; i<textlen; i++) {
		fread(&c, 1, 1, scx);
		text[i]=c;
	}
	text[textlen]='\0';

	long soundlen;
	fread(&soundlen, sizeof(long), 1, scx);

	sound.resize(soundlen);
	for (int i=0; i<soundlen; i++) {
		fread(&c, 1, 1, scx);
		sound[i]=c;
	}
	sound[soundlen]='\0';

	if (num_selected!=-1)
	{
		for (int i=0; i<num_selected; i++)
			fread(&uids[i], sizeof(long), 1, scx);
	}
}

void Effect::write(FILE *scx)
{
	//these are all longs
	fwrite(&type, sizeof(long), 1, scx);
	fwrite(&check_value, sizeof(long), 1, scx);
	fwrite(&ai_goal, sizeof(long), 1, scx);
	fwrite(&amount, sizeof(long), 1, scx);
	fwrite(&resource, sizeof(long), 1, scx);
	fwrite(&diplomacy, sizeof(long), 1, scx);
	fwrite(&num_selected, sizeof(long), 1, scx);
	fwrite(&uid_location, sizeof(long), 1, scx);
	fwrite(&unit_const, sizeof(long), 1, scx);
	fwrite(&player_source, sizeof(long), 1, scx);
	fwrite(&player_target, sizeof(long), 1, scx);
	fwrite(&technology, sizeof(long), 1, scx);
	fwrite(&stableid, sizeof(long), 1, scx);
	fwrite(&unknown, sizeof(long), 1, scx);
	fwrite(&display_time, sizeof(long), 1, scx);
	fwrite(&trigger_index, sizeof(long), 1, scx);

	//it's y then x for some reason
	fwrite(&location.y, sizeof(long), 1, scx);
	fwrite(&location.x, sizeof(long), 1, scx);
	fwrite(&area.ur.y, sizeof(long), 1, scx);
	fwrite(&area.ur.x, sizeof(long), 1, scx);
	fwrite(&area.ll.y, sizeof(long), 1, scx);
	fwrite(&area.ll.x, sizeof(long), 1, scx);

	fwrite(&unit_group, sizeof(long), 1, scx);
	fwrite(&unit_type, sizeof(long), 1, scx);
	fwrite(&panel, sizeof(long), 1, scx);

	long textlen=text.length();
	fwrite(&textlen, sizeof(long), 1, scx);
	fwrite(text.c_str(), sizeof(char), text.length(), scx);

	long soundlen=sound.length();
	fwrite(&soundlen, sizeof(long), 1, scx);
	fwrite(sound.c_str(), sizeof(char), sound.length(), scx);

	if (num_selected>0)
	{
		for (int i=0; i<num_selected; i++)
			fwrite(&uids[i], sizeof(long), 1, scx);
	}
}

bool Effect::check()
{
	switch (type)
	{
	case EFFECT_ChangeDiplomacy:
		return (player_source >= 0 && player_target >= 0 && diplomacy >= 0);

	case EFFECT_ResearchTechnology:
		return (player_source >= 0 && technology >= 0);

	case EFFECT_SendChat:
		return (player_source >= 0 && text.length()>1);	//AOK missing text check

	case EFFECT_PlaySound:
		return (player_source >= 0 && sound.length()>1);	//AOK missing sound check

	case EFFECT_SendTribute:
		return (player_source >= 0 && player_source >= 0 && resource >= 0);

	case EFFECT_UnlockGate:
	case EFFECT_LockGate:
		return (num_selected >= 0);

	case EFFECT_ActivateTrigger:
	case EFFECT_DeactivateTrigger:
		return (trigger_index >= 0);

	case EFFECT_AIScriptGoal:
		return (player_source >= 0 && ai_goal >= 0);

	case EFFECT_CreateObject:
		return (player_source >= 0 &&
			location.x >= 0 && location.y >= 0 && unit_const>=0);

	case EFFECT_TaskObject:
	case EFFECT_KillObject:
	case EFFECT_RemoveObject:
	case EFFECT_FreezeUnit:
	case EFFECT_StopUnit:
		return (num_selected >= 0 || area.ll.x >= 0 || unit_const >= 0);	//AOK missing this

	case EFFECT_DeclareVictory:
		return (player_source >= 0);

	//EFFECT_KillObject, EFFECT_RemoveObject above.

	case EFFECT_ChangeView:
		return (player_source >= 0 && location.x >= 0 && location.y >= 0);

	case EFFECT_Unload:
		return (player_source >= 0
			&& (num_selected >= 0 || area.ll.x >= 0 || unit_const >= 0)	//AOK missing this
			&& location.x >=0 && location.y >= 0);

	case EFFECT_ChangeOwnership:
		return (player_source >= 0 && player_target >= 0
			&& (num_selected >= 0 || area.ll.x >= 0 || unit_type >= 0 || unit_const>=0));	//AOK missing this

	case EFFECT_Patrol:
		return (num_selected >= 0 && location.x >= 0 && location.y >= 0);

	case EFFECT_DisplayInstructions:
		return (panel >= 0 && display_time >= 0
			&& (text.length()>1 || stableid));	//AOK missing text

	case EFFECT_ClearInstructions:
		return (panel >= 0);

	//EFFECT_FreezeUnit above

	case EFFECT_UseAdvancedButtons:
		return true;	//no properties to set

	case EFFECT_DamageObject:
	case EFFECT_ChangeObjectHP:
	case EFFECT_ChangeObjectAttack:
		return (amount != 0 && amount!=-1		//amount can be negative, cannot be -1
			&& (num_selected >= 0 || area.ll.x >= 0));	//AOK missing this

	case EFFECT_PlaceFoundation:
		return (player_source >= 0 && unit_const>=0
			&& location.x >= 0 && location.y >= 0);

	case EFFECT_ChangeObjectName:
		return (num_selected >= 0);	//no text check

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