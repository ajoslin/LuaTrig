
#include "LuaFile.h"
#include "../genie/Trigger.h"
#include "../genie/aok_types.h"
#include <lua.hpp>
#include <string.h>

/* the SWIG wrappered library */
extern "C" int luaopen_Scenario(lua_State* L);

LuaFile *LuaFile::currentLuaFile = NULL;

LuaFile::LuaFile(const char *path)
{
	this->path.assign(path);
}

bool LuaFile::read()
{
	currentLuaFile = this;

	lua_State *L = lua_open();
	// load the libs
	luaL_openlibs(L);
	luaopen_Scenario(L);

	//clear triggers before reading them again
	triggers.clear();
	
	//Read, and record error if it exists
	int has_errors=luaL_dofile(L, path.c_str());

	if (has_errors!=0)
	{
		read_error.assign(lua_tostring(L, -1));
		lua_pop(L, 1); // remove error message
	}
	
	lua_close(L);
	return has_errors!=0;
};

const char *LuaFile::error()
{
	return read_error.c_str();
}

bool LuaFile::add_trigger(Trigger *t, int id)
{
	if (triggers.size()!=id) //if this trigger is not the next id, it's bad
		return false;
	triggers.push_back(t);
	return true;
}

void LuaFile::write(const char *new_path)
{
	FILE *out = fopen(new_path, "w");
	
	//write effect/cond variables at the top
	const char * header = "--Declare variables for use in script\nlocal trigger\nlocal effect\nlocal cond\n\n";
	fwrite(header, 1, strlen(header), out);

	for (int i=0; i<triggers.size(); i++)
		writeTrigger(out, i);
	
	fclose(out);
}

void LuaFile::writeLuaString(FILE *out, const char *str)
{
	std::string fix(str);
	int i;
	//fix backslashes
	i=fix.find("\\", 0);
	while (i!=std::string::npos)
	{
		fix.replace(i, 1, "/");
		i=fix.find("\\", i+1);
	}
	//fix "
	i=fix.find("\"", 0);
	while (i!=std::string::npos)
	{
		fix.replace(i, 1, "\\\"");
		i=fix.find("\"", i+2);
	}
	//fix newlines
	i=fix.find("\n", 0);
	while (i!=std::string::npos)
	{
		fix.replace(i, 1, "\\n");
		i=fix.find("\n", i+2);
	}
	//fix \r
	i=fix.find("\r", 0);
	while (i!=std::string::npos)
	{
		fix.replace(i, 1, "\\r");
		i=fix.find("\r", i+2);
	}
	fprintf(out, "\"%s\"", fix.c_str());
}

void LuaFile::writeTrigger(FILE *out, int id)
{
	const char *trigvar="trigger";

	Trigger *t = triggers.at(id);

	//comment
	fprintf(out, "--Trigger %d\n", id);
	//declaration
	fprintf(out, "%s = Scenario.NewTrigger(%d)\n", trigvar, id);
	//name (always write)
	fprintf(out, "\t%s:name(", trigvar);
	writeLuaString(out, t->name.c_str());
	fprintf(out, ")\n");
	//description (always write)
	fprintf(out, "\t%s:description(", trigvar);
	writeLuaString(out, t->description.c_str());
	fprintf(out, ")\n");
	//on
	fprintf(out, "\t%s:on(%s)\n", trigvar, t->state ? "true" : "false");
	//loop
	fprintf(out, "\t%s:loop(%s)\n", trigvar, t->loop ? "true" : "false");
	//objective
	if (t->obj)
		fprintf(out, "\t%s:objective(%s)\n", trigvar, t->obj ? "true" : "false");
	//objective order
	if (t->obj || t->obj_order)
		fprintf(out, "\t%s:desc_order(%d)\n", trigvar, t->obj_order);
	
	//Conditions
	const char *condvar = "cond";
	for (int i=0; i<t->conds.size(); i++)
	{
		Condition *c = t->conds.at(i);
		
		//comment
		fprintf(out, "\t--Condition %d %s\n", i, c->getName());
		//declaration
		fprintf(out, "\t%s = %s:Condition%s()\n", condvar, trigvar, c->getName());
		//amount
		if (c->getAmount()!=-1)
			fprintf(out, "\t\t%s:amount(%d)\n", condvar, c->getAmount());
		//resource type
		if (c->getResource()!=-1)
			fprintf(out, "\t\t%s:resource(\"%s\") --aka resource(%d)\n",
				condvar, genieResources->nameFromId(c->getResource()), c->getResource());
		//unit object
		if (c->getUidObject()!=-1)
			fprintf(out, "\t\t%s:unit_object(%d)\n", condvar, c->getUidObject());
		//unit location
		if (c->getUidLocation()!=-1)
			fprintf(out, "\t\t%s:unit_location(%d)\n", condvar, c->getUidLocation());
		//unit const
		if (c->getUnitConst()!=-1)
			fprintf(out, "\t\t%s:unit_const(%d)\n", condvar, c->getUnitConst());
		//player
		if (c->getPlayer()!=-1)
			fprintf(out, "\t\t%s:player(%d)\n", condvar, c->getPlayer());
		//technology
		if (c->getTechnology()!=-1)
			fprintf(out, "\t\t%s:tech(%d)\n", condvar, c->getTechnology());
		//timer
		if (c->getTimer()!=-1)
			fprintf(out, "\t\t%s:time(%d)\n", condvar, c->getTimer());
		//area
		if (c->getArea().ur.x!=-1 && c->getArea().ll.x!=-1)
			fprintf(out, "\t\t%s:area(%d,%d, %d,%d)\n", 
				condvar, c->getArea().ll.x, c->getArea().ll.y, c->getArea().ur.x, c->getArea().ur.y);
		//unit group
		if (c->getUnitGroup()!=-1)
			fprintf(out, "\t\t%s:unit_group(\"%s\")\n",
				 condvar, genieUnitGroups->nameFromId(c->getUnitGroup()), c->getUnitGroup()); 
		//unit type
		if (c->getUnitType()!=-1)
			fprintf(out, "\t\t%s:unit_type(\"%s\")\n",
				condvar, genieUnitTypes->nameFromId(c->getUnitType()), c->getUnitType());
		//ai signal
		if (c->getAiSignal()!=-1)
			fprintf(out, "\t\t%s:ai_signal(%d)\n", condvar, c->getAiSignal());
	}

	//Effects
	const char *effectvar="effect";
	for (int i=0; i<t->effects.size(); i++)
	{
		Effect *e = t->effects.at(i);

		//comment
		fprintf(out, "\t--Effect %d %s\n", i, e->getName());
		//declaration
		fprintf(out, "\t%s = %s:Effect%s()\n", effectvar, trigvar, e->getName());
		//ai goal
		if (e->getAiGoal()!=-1)
			fprintf(out, "\t\t%s:ai_goal(%d)\n", effectvar, e->getAiGoal());
		//amount
		if (e->getAmount()!=-1)
			fprintf(out, "\t\t%s:amount(%d)\n", effectvar, e->getAmount());
		//resource
		if (e->getResource()!=-1)
			fprintf(out, "\t\t%s:resource(\"%s\")\n",
				effectvar, genieResources->nameFromId(e->getResource()), e->getResource());
		//diplomacy
		if (e->getDiplomacy()!=-1)
			fprintf(out, "\t\t%s:diplomacy(\"%s\")\n",
				effectvar, genieDiplomacies->nameFromId(e->getDiplomacy()), e->getDiplomacy());
		//unit location
		if (e->getUidLocation()!=-1)
			fprintf(out, "\t\t%s:unit_location(%d)\n", effectvar, e->getUidLocation());
		//unit const
		if (e->getUnitConst()!=-1)
			fprintf(out, "\t\t%s:unit_const(%d)\n", effectvar, e->getUnitConst());
		//selected unit(s)
		if (e->getUids().size()>0)
		{
			fprintf(out, "\t\t%s:units(", effectvar);
			for (int i=0; i<e->getUids().size(); i++)
			{
				fprintf(out, "%d", e->getUids()[i]);
				if (i<e->getUids().size()-1) //add comma on all except last
					fprintf(out, ", ");
			}
			fprintf(out, ")\n"); 
		}
		//player_source
		if (e->getPlayerSource()!=-1)
			fprintf(out, "\t\t%s:p_source(%d)\n", effectvar, e->getPlayerSource());
		//player_target
		if (e->getPlayerTarget()!=-1)
			fprintf(out, "\t\t%s:p_target(%d)\n", effectvar, e->getPlayerTarget());
		//technology
		if (e->getTechnology()!=-1)
			fprintf(out, "\t\t%s:tech(%d)\n", effectvar, e->getTechnology());
		//display time
		if (e->getDisplayTime()!=-1)
			fprintf(out, "\t\t%s:time(%d)\n", effectvar, e->getDisplayTime());
		//trigger index
		if (e->getTriggerIndex()>=0)
			fprintf(out, "\t\t%s:trigger(%d)\n", effectvar, e->getTriggerIndex());
		//location
		if (e->getLocation().x!=-1)
			fprintf(out, "\t\t%s:location(%d,%d)\n", effectvar, e->getLocation().x, e->getLocation().y);
		//area
		if (e->getArea().ur.x!=-1 && e->getArea().ll.x!=-1)
			fprintf(out, "\t\t%s:area(%d,%d, %d,%d)\n", 
				effectvar, e->getArea().ll.x, e->getArea().ll.y, e->getArea().ur.x, e->getArea().ur.y); 
		//unit group
		if (e->getUnitGroup()!=-1)
			fprintf(out, "\t\t%s:unit_group(\"%s\")\n",
				 effectvar, genieUnitGroups->nameFromId(e->getUnitGroup()), e->getUnitGroup()); 
		//unit type
		if (e->getUnitType()!=-1)
			fprintf(out, "\t\t%s:unit_type(\"%s\")\n",
				effectvar, genieUnitTypes->nameFromId(e->getUnitType()), e->getUnitType()); 
		//panel
		if (e->getPanel()!=-1)
			fprintf(out, "\t\t%s:panel(%d)\n", effectvar, e->getPanel());
		//text
		if (e->getText().length()>1)
		{
			fprintf(out, "\t\t%s:text(", effectvar);
			writeLuaString(out, e->getText().c_str());
			fprintf(out, ")\n");
		}
		//sound
		if (e->getSound().length()>1)
		{
			fprintf(out, "\t\t%s:sound(", effectvar);
			writeLuaString(out, e->getSound().c_str());
			fprintf(out, ")\n");	
		}
	}
	//ending \n for two lines between each trigger
	//fprintf(out, "\n"); 
	//*/
}

LuaFile *LuaFile::current()
{
	return LuaFile::currentLuaFile;
}


