#include "Condition.h"
#include "ConditionTypes.h"

Condition::Condition(long t)
{
	type = t;
	unknown = -1;
	check_value = 0x10;
}

Condition *Condition::createType(long type)
{
	switch(type)
	{
	case CONDITION_BringObjectToArea:
		return new Condition_BringObjectToArea();
	case CONDITION_BringObjectToObject:
		return new Condition_BringObjectToObject();
	case CONDITION_OwnObjects:
		return new Condition_OwnObjects();
	case CONDITION_OwnFewerObjects:
		return new Condition_OwnFewerObjects();
	case CONDITION_ObjectsInArea:
		return new Condition_ObjectsInArea();
	case CONDITION_DestroyObject:
		return new Condition_DestroyObject();
	case CONDITION_CaptureObject:
		return new Condition_CaptureObject();
	case CONDITION_AccumulateAttribute:
		return new Condition_AccumulateAttribute();
	case CONDITION_ResearchTechnology:
		return new Condition_ResearchTechnology();
	case CONDITION_Timer:
		return new Condition_Timer();
	case CONDITION_ObjectSelected:
		return new Condition_ObjectSelected();
	case CONDITION_AISignal:
		return new Condition_AISignal();
	case CONDITION_PlayerDefeated:
		return new Condition_PlayerDefeated();
	case CONDITION_ObjectHasTarget:
		return new Condition_ObjectHasTarget();
	case CONDITION_ObjectVisible:
		return new Condition_ObjectVisible();
	case CONDITION_ObjectNotVisible:
		return new Condition_ObjectNotVisible();
	case CONDITION_ResearchingTechnology:
		return new Condition_ResearchingTechnology();
	case CONDITION_UnitsGarrisoned:
		return new Condition_UnitsGarrisoned();
	case CONDITION_DifficultyLevel:
		return new Condition_DifficultyLevel();
	default:
		return new Condition_None();
	}
}

const char * Condition::getName() {
	return (type < NUM_CONDS) ? types[type] : "Unknown!";
}

void Condition::read(FILE *scx)
{
	fread(&check_value, sizeof(long), 1, scx);
	readAmount(scx);
	readResource(scx);
	readUidObject(scx);
	readUidLocation(scx);
	readUnitConst(scx);
	readPlayer(scx);
	readTechnology(scx);
	readTimer(scx);
	fread(&unknown, 4, 1, scx);
	readArea(scx);
	readUnitGroup(scx);
	readUnitType(scx);
	readAiSignal(scx);
}

void Condition::write(FILE *scx)
{
	long amount=getAmount();
	long res=getResource();
	long uid_obj=getUidObject();
	long uid_loc=getUidLocation();
	long uconst=getUnitConst();
	long player=getPlayer();
	long tech=getTechnology();
	long timer=getTimer();
	AOKRECT area=getArea();
	long ugroup=getUnitGroup();
	long utype=getUnitType();
	long aisignal=getAiSignal();

	fwrite(&type, sizeof(long), 1, scx);
	fwrite(&check_value, sizeof(long), 1, scx);
	fwrite(&amount, sizeof(long), 1, scx);
	fwrite(&res, sizeof(long), 1, scx);
	fwrite(&uid_obj, sizeof(long), 1, scx);
	fwrite(&uid_loc, sizeof(long), 1, scx);
	fwrite(&uconst, sizeof(long), 1, scx);
	fwrite(&player, 4, 1, scx);
	fwrite(&tech, 4, 1, scx);
	fwrite(&timer, 4, 1, scx);
	fwrite(&unknown, 4, 1, scx);
	fwrite(&area.ur.y, 4, 1, scx); //aok points are y,x for some reason
	fwrite(&area.ur.x, 4, 1, scx);
	fwrite(&area.ll.y, 4, 1, scx);
	fwrite(&area.ll.x, 4, 1, scx);
	fwrite(&ugroup, 4, 1, scx);
	fwrite(&utype, 4, 1, scx);
	fwrite(&aisignal, 4, 1, scx);
}

bool Condition::check()
{
	switch (type)
	{
	case CONDITION_BringObjectToArea:
		return (getUidObject() >= 0 && getArea().ll.x >= 0);

	case CONDITION_BringObjectToObject:
		return (getUidObject() >= 0 && getUidLocation() >= 0);

	case CONDITION_OwnObjects:
	case CONDITION_OwnFewerObjects:
		return (getPlayer() >= 0 && getAmount() >= 0);

	case CONDITION_ObjectsInArea:
		return (getArea().ll.x >= 0 && getAmount() >= 0);

	case CONDITION_DestroyObject:
		return (getUidObject() >= 0);

	case CONDITION_CaptureObject:
		return (getUidObject() >= 0 && getPlayer() >= 0);

	case CONDITION_AccumulateAttribute:
		return (getPlayer() >= 0 && getResource() >= 0);

	case CONDITION_ResearchTechnology:
	case CONDITION_ResearchingTechnology:
		return (getPlayer() >= 0 && getTechnology() >= 0);

	case CONDITION_Timer:
		return (getTimer() >= 0);

	case CONDITION_ObjectSelected:
		return (getUidObject() >= 0);

	case CONDITION_AISignal:
		return (getAiSignal() >= 0);

	case CONDITION_PlayerDefeated:
		return (getPlayer() >= 0);

	case CONDITION_ObjectHasTarget:
		return (getUidObject() >= 0 && getUidLocation() >= 0);

	case CONDITION_ObjectVisible:
	case CONDITION_ObjectNotVisible:
		return (getUidObject() >= 0);

	//CONDITION_ResearchingTechnology above

	case CONDITION_UnitsGarrisoned:
		return (getUidObject() >= 0 && getAmount() >= 0);

	case CONDITION_DifficultyLevel:
		return (getAmount() >= 0);

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

const char *Condition::propertyTypes[] =
{
	"Amount",
	"Resource",
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

