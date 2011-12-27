#include "NewTrigger.h"
#include "LuaFile.h"
#include "LCondition.h"
//#include "LEffect.h"
#include "../genie/Trigger.h"
#include <string.h>

NewTrigger::NewTrigger(int id) throw(char *)
{
	trig = new Trigger;
	if (!LuaFile::current()->add_trigger(trig, id))
	{
		char *err = new char[75];
		sprintf(err, "Could not create trigger with ID=%d. Expected ID consecutive to that of previous trigger and nonnegative.");
		throw(err);
		delete this;
	}
}

void NewTrigger::name(const char *name) throw(char *)
{
	if (strlen(name)>=trig->MAX_TRIGNAME)
	{
		char *err = new char[75];
		sprintf(err, "Could not assign name given. Exceeds maximum name length of %d.", trig->MAX_TRIGNAME);
	} 
	else
	{
		trig->name.assign(name);
	}
}

void NewTrigger::description(const char *description)
{
	trig->description.assign(description);
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
	trig->loop=(isloop==true ? 1 : 0);
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

void NewTrigger::desc_order(int order) throw(char *)
{
	if (order<0)
	{
		char *err = new char[75];
		sprintf(err, "Could not assign desc_order of %d. Expected nonnegative integer.");
		throw(err);
	} 
	else
	{
		trig->obj_order=order;
	}
}

LCondition *NewTrigger::condition(int type) throw(char *)
{
	if (type<0 || type>MAX_CONDITION)
	{
		char *err=new char[75];
		sprintf(err, "Could not create condition of type %d. Expected type between 0 and %d.", type, MAX_CONDITION);
		throw(err);
	}
	else
	{
		Condition *c = new Condition();
		c->type = type;
		LCondition *lc = new LCondition(c);
		trig->conds.push_back(c);
		return lc;
	}
}

Effect *NewTrigger::effect(int type) throw(char *)
{
	return NULL;
}