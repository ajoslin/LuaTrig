#include "Condition.h"

Condition::Condition()
{
	check_value=0x10;
	type = amount = resource_type = uid_object = uid_location = player = technology = -1;
	timer = unknown = unit_group = unit_type = unit_const = ai_signal = -1;
}

const char * Condition::getName() {
	return (type < NUM_CONDS) ? types[type] : "Unknown!";
}

void Condition::read(FILE *scx)
{
	fread(&type, sizeof(long), 1, scx);
	fread(&check_value, sizeof(long), 1, scx);
	fread(&amount, sizeof(long), 1, scx);
	fread(&resource_type, sizeof(long), 1, scx);
	fread(&uid_object, sizeof(long), 1, scx);
	fread(&uid_location, sizeof(long), 1, scx);
	fread(&unit_const, sizeof(long), 1, scx);
	fread(&player, 4, 1, scx);
	fread(&technology, 4, 1, scx);
	fread(&timer, 4, 1, scx);
	fread(&unknown, 4, 1, scx);

	//aok points are y,x for some reason
	fread(&area.ur.y, 4, 1, scx);
	fread(&area.ur.x, 4, 1, scx);
	fread(&area.ll.y, 4, 1, scx);
	fread(&area.ll.x, 4, 1, scx);

	fread(&unit_group, 4, 1, scx);
	fread(&unit_type, 4, 1, scx);
	fread(&ai_signal, 4, 1, scx);
}

void Condition::write(FILE *scx)
{
	fwrite(&type, sizeof(long), 1, scx);
	fwrite(&check_value, sizeof(long), 1, scx);
	fwrite(&amount, sizeof(long), 1, scx);
	fwrite(&resource_type, sizeof(long), 1, scx);
	fwrite(&uid_object, sizeof(long), 1, scx);
	fwrite(&uid_location, sizeof(long), 1, scx);
	fwrite(&unit_const, sizeof(long), 1, scx);
	fwrite(&player, 4, 1, scx);
	fwrite(&technology, 4, 1, scx);
	fwrite(&timer, 4, 1, scx);
	fwrite(&unknown, 4, 1, scx);

	//aok points are y,x for some reason
	fwrite(&area.ur.y, 4, 1, scx);
	fwrite(&area.ur.x, 4, 1, scx);
	fwrite(&area.ll.y, 4, 1, scx);
	fwrite(&area.ll.x, 4, 1, scx);

	fwrite(&unit_group, 4, 1, scx);
	fwrite(&unit_type, 4, 1, scx);
	fwrite(&ai_signal, 4, 1, scx);
}

bool Condition::check()
{
	switch (type)
	{
	case CONDITION_BringObjectToArea:
		return (uid_object >= 0 && area.ll.x >= 0);

	case CONDITION_BringObjectToObject:
		return (uid_object >= 0 && uid_location >= 0);

	case CONDITION_OwnObjects:
	case CONDITION_OwnFewerObjects:
		return (player >= 0 && amount >= 0);

	case CONDITION_ObjectsInArea:
		return (area.ll.x >= 0 && amount >= 0);

	case CONDITION_DestroyObject:
		return (uid_object >= 0);

	case CONDITION_CaptureObject:
		return (uid_object >= 0 && player >= 0);

	case CONDITION_AccumulateAttribute:
		return (player >= 0 && resource_type >= 0);

	case CONDITION_ResearchTechnology:
	case CONDITION_ResearchingTechnology:
		return (player >= 0 && technology >= 0);

	case CONDITION_Timer:
		return (timer >= 0);

	case CONDITION_ObjectSelected:
		return (uid_object >= 0);

	case CONDITION_AISignal:
		return (ai_signal >= 0);

	case CONDITION_PlayerDefeated:
		return (player >= 0);

	case CONDITION_ObjectHasTarget:
		return (uid_object >= 0 && uid_location >= 0);

	case CONDITION_ObjectVisible:
	case CONDITION_ObjectNotVisible:
		return (uid_object >= 0);

	//CONDITION_ResearchingTechnology above

	case CONDITION_UnitsGarrisoned:
		return (uid_object >= 0 && amount >= 0);

	case CONDITION_DifficultyLevel:
		return (amount >= 0);

	//CONDITION_OwnFewerFoundations shares with OwnObjects above
	//CONDITION_SelectedObjectsInArea shares with ObjectsInArea above
	//CONDITION_PoweredObjectsInArea shares with ObjectsInArea above
	//CONDITION_UnitsQueuedPastPopCap shares with PlayerDefeated above

	default:
		return false;
	}
}

bool Condition::valid_property(ConditionProperty p)
{
	switch (type)
	{
	case CONDITION_None:
		return false;

	case CONDITION_BringObjectToArea:
		return (p==CONDITIONP_UIDObject || p==CONDITIONP_Area);

	case CONDITION_BringObjectToObject:
		return (p==CONDITIONP_UIDObject || p==CONDITIONP_UIDLocation);

	case CONDITION_OwnObjects:
	case CONDITION_OwnFewerObjects:
		return (CONDITIONP_Player==p || CONDITIONP_Amount==p || CONDITIONP_UnitConst==p || CONDITIONP_UnitType==p || CONDITIONP_UnitGroup==p);

	case CONDITION_ObjectsInArea:
		return (CONDITIONP_Area==p || CONDITIONP_Player==p || CONDITIONP_Amount==p || CONDITIONP_UnitConst==p || CONDITIONP_UnitType==p || CONDITIONP_UnitGroup==p);

	case CONDITION_DestroyObject:
		return (CONDITIONP_UIDObject==p);

	case CONDITION_CaptureObject:
		return (CONDITIONP_UIDObject==p || CONDITIONP_Player==p);

	case CONDITION_AccumulateAttribute:
		return (CONDITIONP_Player==p || CONDITIONP_ResourceType==p || CONDITIONP_Amount==p);

	case CONDITION_ResearchTechnology:
	case CONDITION_ResearchingTechnology:
		return (CONDITIONP_Player==p || CONDITIONP_Technology==p);

	case CONDITION_Timer:
		return (CONDITIONP_Timer==p || CONDITIONP_Amount==p);

	case CONDITION_ObjectSelected:
		return (CONDITIONP_UIDObject==p);

	case CONDITION_AISignal:
		return (CONDITIONP_AISignal==p);

	case CONDITION_PlayerDefeated:
		return (CONDITIONP_Player==p);

	case CONDITION_ObjectHasTarget:
		return (CONDITIONP_UIDObject==p || CONDITIONP_UIDLocation==p || CONDITIONP_UnitConst==p || CONDITIONP_UnitType==p || CONDITIONP_UnitGroup==p);

	case CONDITION_ObjectVisible:
	case CONDITION_ObjectNotVisible:
		return (CONDITIONP_UIDObject==p);

	//CONDITION_ResearchingTechnology above

	case CONDITION_UnitsGarrisoned:
		return (CONDITIONP_UIDObject==p || CONDITIONP_Amount==p);

	case CONDITION_DifficultyLevel:
		return (CONDITIONP_Amount==p);

	//CONDITION_OwnFewerFoundations shares with OwnObjects above
	//CONDITION_SelectedObjectsInArea shares with ObjectsInArea above
	//CONDITION_PoweredObjectsInArea shares with ObjectsInArea above
	//CONDITION_UnitsQueuedPastPopCap shares with PlayerDefeated above

	default:
		return false;
	}
}

const char *Condition::types[] =
{
	"None",
	"BringObjectToArea",
	"BringObjectToObject",
	"OwnObjects",
	"OwnFewerObjects",
	"ObjectsInArea",
	"DestroyObject",
	"CaptureObject",
	"AccumulateAttribute",
	"ResearchTechnology",
	"Timer",
	"ObjectSelected",
	"AISignal",
	"PlayerDefeated",
	"ObjectHasTarget",
	"ObjectVisible",
	"ObjectNotVisible",
	"ResearchingTechnology",
	"UnitsGarrisoned",
	"DifficultyLevel",
};

const char *Condition::partypes[] =
{
	"Amount",
	"ResourceType",
	"UIDObject",
	"UIDLocation",
	"Player",
	"Technology",
	"Timer",
	"Area",
	"UnitGroup",
	"UnitType",
	"UnitConst",
	"AISignal",
};