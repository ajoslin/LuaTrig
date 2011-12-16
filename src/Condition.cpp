#include "../include/Condition.h"
#include "../include/fileutil.h"

Condition::Condition()
{
	check_value=0x10;
	type = amount = resource_type = uid_object = uid_location = player = technology = -1;
	timer = unknown = unit_group = unit_type = unit_const = ai_signal = -1;
}

const std::string Condition::getName() const {
	return (type < NUM_CONDS) ? types[type] : "Unknown!";
}

int Condition::readfromscx(FILE *scx)
{
	long bytes_read=0;

	READ(&type, sizeof(long), 1, scx);
	READ(&check_value, sizeof(long), 1, scx);
	READ(&amount, sizeof(long), 1, scx);
	READ(&resource_type, sizeof(long), 1, scx);
	READ(&uid_object, sizeof(long), 1, scx);
	READ(&uid_location, sizeof(long), 1, scx);
	READ(&unit_const, sizeof(long), 1, scx);
	READ(&player, 4, 1, scx);
	READ(&technology, 4, 1, scx);
	READ(&timer, 4, 1, scx);
	READ(&unknown, 4, 1, scx);

	//aok points are y,x for some reason
	READ(&area.ur.y, 4, 1, scx);
	READ(&area.ur.x, 4, 1, scx);
	READ(&area.ll.y, 4, 1, scx);
	READ(&area.ll.x, 4, 1, scx);

	READ(&unit_group, 4, 1, scx);
	READ(&unit_type, 4, 1, scx);
	READ(&ai_signal, 4, 1, scx);

	return bytes_read; 
}

void Condition::writetoscx(FILE *scx)
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

void Condition::writetolua(FILE *out, const char *trigvar, const char* condvar)
{
	//condition declaration
	fprintf(out, "\tlocal %s = %s:condition(Condition.%s())\n", condvar, trigvar, getName().c_str());
	//amount
	if (amount!=-1)
		fprintf(out, "\t\t%s:amount(%d)\n", condvar, amount);
	//resource type
	if (resource_type!=-1) 
		fprintf(out, "\t\t%s:resource(\"%s\") --could also be written resource(%d)\n",
			condvar, aokutil::get_res_str(resource_type), resource_type);
	//unit object
	if (uid_object!=-1)
		fprintf(out, "\t\t%s:unit_object(%d)\n", condvar, uid_object);
	//unit location
	if (uid_location!=-1)
		fprintf(out, "\t\t%s:unit_location(%d)\n", condvar, uid_location);
	//unit const
	if (unit_const!=-1)
		fprintf(out, "\t\t%s:unit_const(%d)\n", condvar, unit_const);
	//player
	if (player!=-1)
		fprintf(out, "\t\t%s:player(%d)\n", condvar, player);
	//technology
	if (technology!=-1)
		fprintf(out, "\t\t%s:technology(%d)\n", condvar, technology);
	//timer (uses amount() function in lua)
	if (timer!=-1)
		fprintf(out, "\t\t%s:amount(%d)\n", condvar, timer);
	//area
	if (area.ur.x!=-1 && area.ll.x!=-1)
		fprintf(out, "\t\t%s:area(%d,%d, %d,%d) --usage: lower left x1,y1 then upper right x2,y2\n", 
			condvar, area.ll.x, area.ll.y, area.ur.x, area.ur.y);
	//unit group
	if (unit_group!=-1)
		fprintf(out, "\t\t%s:unit_group(\"%s\") --could also be written unit_group(%d)\n",
			 condvar, aokutil::get_ugroup_str(unit_group), unit_group);
	//unit type
	if (unit_type!=-1)
		fprintf(out, "\t\t%s:unit_type(\"%s\") --could also be written unit_type(%d)\n",
			condvar, aokutil::get_utype_str(unit_type), unit_type);
	//ai signal
	if (ai_signal!=-1)
		fprintf(out, "\t\t%s:ai_signal(%d)\n", condvar, ai_signal);
}


bool Condition::check() const
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

bool Condition::valid_property(ConditionProperty p) const
{
	switch (type)
	{
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