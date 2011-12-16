
#include "Effect.h"

Effect::Effect()
{
	check_value=0x17;
	ai_goal;
	amount = diplomacy = display_time = num_selected = panel = player_source = -1;
	player_target = resource = stableid = technology = trigger_index = type = uid_location = -1;
	unit_group = unit_type = unit_const = unknown = -1;
	memset(uids, -1, sizeof(uids));
}

int Effect::readfromscx(FILE *scx)
{
	long bytes_read=0;

	//these are all longs
	READ(&type, sizeof(long), 1, scx);
	READ(&check_value, sizeof(long), 1, scx);
	READ(&ai_goal, sizeof(long), 1, scx);
	READ(&amount, sizeof(long), 1, scx);
	READ(&resource, sizeof(long), 1, scx);
	READ(&diplomacy, sizeof(long), 1, scx);
	READ(&num_selected, sizeof(long), 1, scx);
	READ(&uid_location, sizeof(long), 1, scx);
	READ(&unit_const, sizeof(long), 1, scx);
	READ(&player_source, sizeof(long), 1, scx);
	READ(&player_target, sizeof(long), 1, scx);
	READ(&technology, sizeof(long), 1, scx);
	READ(&stableid, sizeof(long), 1, scx);
	READ(&unknown, sizeof(long), 1, scx);
	READ(&display_time, sizeof(long), 1, scx);
	READ(&trigger_index, sizeof(long), 1, scx);

	//it's y then x for some reason
	READ(&location.y, sizeof(long), 1, scx);
	READ(&location.x, sizeof(long), 1, scx);
	READ(&area.ur.y, sizeof(long), 1, scx);
	READ(&area.ur.x, sizeof(long), 1, scx);
	READ(&area.ll.y, sizeof(long), 1, scx);
	READ(&area.ll.x, sizeof(long), 1, scx);

	READ(&unit_group, sizeof(long), 1, scx);
	READ(&unit_type, sizeof(long), 1, scx);
	READ(&panel, sizeof(long), 1, scx);

	long textlen;
	READ(&textlen, sizeof(long), 1, scx);

	text.resize(textlen);
	for (int i=0; i<textlen; i++) {
		char c=text.at(i);
		READ(&c, 1, 1, scx);
	}
	//text.at(textlen)='\0'; //make sure it's null terminated

	long soundlen;
	READ(&soundlen, sizeof(long), 1, scx);

	sound.resize(soundlen);
	for (int i=0; i<soundlen; i++) {
		char c=sound.at(i);
		READ(&c, 1, 1, scx);
	}
	//sound.at(soundlen)='\0'; //make sure it's null terminated

	if (num_selected!=-1)
	{
		for (int i=0; i<num_selected; i++)
			READ(&uids[i], sizeof(long), 1, scx);
	}

	return bytes_read;
}

void Effect::writetoscx(FILE *scx)
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

void Effect::writetolua(FILE *out, const char *trigvar, const char* effectvar)
{
	//condition declaration
	fprintf(out, "\tlocal %s = %s:effect(Effect.%s())\n", effectvar, trigvar, getName().c_str());
	//ai goal
	if (ai_goal!=-1)
		fprintf(out, "\t\t%s:ai_goal(%d)\n", effectvar, ai_goal);
	//amount
	if (amount!=-1)
		fprintf(out, "\t\t%s:amount(%d)\n", effectvar, amount);
	//resource
	if (resource!=-1) 
		fprintf(out, "\t\t%s:resource(\"%s\") --could also be written resource(%d)\n",
			effectvar, my_util::get_res_str(resource), resource);
	//diplomacy
	if (diplomacy!=-1)
		fprintf(out, "\t\t%s:diplomacy(\"%s\") --could also be written diplomacy(%d)\n",
			effectvar, my_util::get_diplomacy_str(diplomacy), diplomacy);
	//unit location
	if (uid_location!=-1)
		fprintf(out, "\t\t%s:unit_location(%d)\n", effectvar, uid_location);
	//unit const
	if (unit_const!=-1)
		fprintf(out, "\t\t%s:unit_const(%d)\n", effectvar, unit_const);
	//selected unit(s)
	if (num_selected!=-1)
	{
		fprintf(out, "\t\t%s:units(", effectvar);
		for (int i=0; i<num_selected; i++)
		{
			fprintf(out, "%d", uids[i]);
			if (i<num_selected-1) //add comma on all except last
				fprintf(out, ", ");
		}
		fprintf(out, ")\n");
	}
	//player_source
	if (player_source!=-1)
		fprintf(out, "\t\t%s:player(%d)\n", effectvar, player_source);
	//player_target
	if (player_target!=-1)
		fprintf(out, "\t\t%s:player_target(%d)\n", effectvar, player_target);
	//technology
	if (technology!=-1)
		fprintf(out, "\t\t%s:technology(%d)\n", effectvar, technology);
	//display time
	if (display_time!=-1)
		fprintf(out, "\t\t%s:display_time(%d)\n", effectvar, display_time);
	//trigger index
	if (trigger_index!=-1)
		fprintf(out, "\t\t%s:trigger(%d)\n", effectvar, trigger_index);
	//location
	if (location.x!=-1)
		fprintf(out, "\t\t%s:location(%d,%d)\n", effectvar, location.x, location.y);
	//area
	if (area.ur.x!=-1 && area.ll.x!=-1)
		fprintf(out, "\t\t%s:area(%d,%d, %d,%d) --lower left x1,y1 then upper right x2,y2\n", 
			effectvar, area.ll.x, area.ll.y, area.ur.x, area.ur.y);
	//unit group
	if (unit_group!=-1)
		fprintf(out, "\t\t%s:unit_group(\"%s\") --could also be written unit_group(%d)\n",
			 effectvar, my_util::get_ugroup_str(unit_group), unit_group);
	//unit type
	if (unit_type!=-1)
		fprintf(out, "\t\t%s:unit_type(\"%s\") --could also be written unit_type(%d)\n",
			effectvar, my_util::get_utype_str(unit_type), unit_type);
	//panel
	if (panel!=-1)
		fprintf(out, "\t\t%s:panel(%d)\n", effectvar, panel);
	//text
	if (text.length()>1)
		fprintf(out, "\t\t%s:text(\"%s\")\n", effectvar, text.c_str());
	//sound
	if (sound.length()>1)
		fprintf(out, "\t\t%s:sound(\"%s\")\n", effectvar, sound.c_str());	
}

const string Effect::getName() const
{
	return (type < NUM_EFFECTS) ? types[type] : "Unknown!";
}

bool Effect::check() const
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

bool Effect::valid_property(EffectProperty p) const
{
	switch (type)
	{
	case EFFECT_ChangeDiplomacy:
		return (EFFECTP_PlayerSource==p || EFFECTP_PlayerTarget==p || EFFECTP_Diplomacy==p);

	case EFFECT_ResearchTechnology:
		return (EFFECTP_PlayerSource==p || EFFECTP_Technology==p);

	case EFFECT_SendChat:
		return (EFFECTP_PlayerSource==p || EFFECTP_Text==p || EFFECTP_Sound==p);

	case EFFECT_PlaySound:
		return (EFFECTP_PlayerSource==p || EFFECTP_Sound==p);

	case EFFECT_SendTribute:
		return (EFFECTP_PlayerSource==p || EFFECTP_PlayerTarget==p || EFFECTP_Amount==p || EFFECTP_Resource==p);

	case EFFECT_UnlockGate:
	case EFFECT_LockGate:
		return (EFFECTP_UIDs==p);

	case EFFECT_ActivateTrigger:
	case EFFECT_DeactivateTrigger:
		return (EFFECTP_TriggerIndex==p);

	case EFFECT_AIScriptGoal:
		return (EFFECTP_PlayerSource==p || EFFECTP_AIGoal==p);

	case EFFECT_CreateObject:
		return (EFFECTP_PlayerSource==p || EFFECTP_Location==p || EFFECTP_UnitConst==p);

	case EFFECT_TaskObject:
	case EFFECT_KillObject:
	case EFFECT_RemoveObject:
	case EFFECT_FreezeUnit:
	case EFFECT_StopUnit:
		return (EFFECTP_UnitGroup==p || EFFECTP_Location==p || EFFECTP_UIDs==p || EFFECTP_PlayerSource==p || EFFECTP_Area==p || EFFECTP_UnitConst==p || EFFECTP_UnitType==p);

	case EFFECT_DeclareVictory:
		return (EFFECTP_PlayerSource==p);

	//EFFECT_KillObject, EFFECT_RemoveObject above.

	case EFFECT_ChangeView:
		return (EFFECTP_PlayerSource==p || EFFECTP_Location==p);

	case EFFECT_Unload:
		return (EFFECTP_UnitGroup==p || EFFECTP_PlayerSource==p || EFFECTP_Location==p || EFFECTP_UIDLocation==p || EFFECTP_Area==p || EFFECTP_UnitConst==p || EFFECTP_UnitType==p);

	case EFFECT_ChangeOwnership:
		return (EFFECTP_PlayerSource==p || EFFECTP_PlayerTarget==p || EFFECTP_Area==p || EFFECTP_UnitConst==p || EFFECTP_UnitType==p);

	case EFFECT_Patrol:
		return (EFFECTP_UIDs==p || EFFECTP_Location==p);

	case EFFECT_DisplayInstructions:
		return (EFFECTP_Panel==p || EFFECTP_DisplayTime==p || EFFECTP_Text==p || EFFECTP_Sound==p);

	case EFFECT_ClearInstructions:
		return (EFFECTP_Panel==p);

	//EFFECT_FreezeUnit above

	case EFFECT_UseAdvancedButtons:
		return false;	//no properties to set

	case EFFECT_DamageObject:
	case EFFECT_ChangeObjectHP:
	case EFFECT_ChangeObjectAttack:
		return (EFFECTP_UnitGroup==p || EFFECTP_UIDs==p || EFFECTP_Amount==p || EFFECTP_PlayerSource==p || EFFECTP_PlayerTarget==p || EFFECTP_Area==p || EFFECTP_UnitConst==p || EFFECTP_UnitType==p);

	case EFFECT_PlaceFoundation:
		return (EFFECTP_UnitConst==p || EFFECTP_PlayerSource==p || EFFECTP_UnitConst==p);

	case EFFECT_ChangeObjectName:
		return (EFFECTP_UIDs==p || EFFECTP_Text==p);	//no text check

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
