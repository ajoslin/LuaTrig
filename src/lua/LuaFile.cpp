
#include "LuaFile.h"
#include "../genie/Trigger.h"
#include "../defines.h"
#include "../util/aokutil.h"
#include "../genie/aok_types.h"
#include <lua.hpp>
#include <string.h>

/* the SWIG wrappered library */
extern "C" int luaopen_Scenario(lua_State*L);

LuaFile *LuaFile::currentLuaFile = NULL;

LuaFile::LuaFile(const char *_path, int len)
{
	path = new char[len+1];
	for (int i=0; i<len; i++)
	path[i] = _path[i];
	path[len+1]='\0';
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
	int has_errors=luaL_dofile(L, path);

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
	const char * locals = "--Declare variables for use in script\nlocal trigger\nlocal effect\nlocal cond\n\n";
	fwrite(locals, 1, strlen(locals), out);

	for (int i=0; i<triggers.size(); i++)
		writeTrigger(out, i);
	
	fclose(out);
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
	fprintf(out, "\t%s:name(\"%s\")\n", trigvar, t->name.c_str());
	//description (always write)
	fprintf(out, "\t%s:description(\"%s\")\n", trigvar, t->description.c_str());
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
		fprintf(out, "\t%s = %s:condition_%s()\n", condvar, trigvar, c->getName());
		//amount
		if (c->amount!=-1 && c->valid_property(CONDITIONP_Amount))
			fprintf(out, "\t\t%s:amount(%d)\n", condvar, c->amount);
		//resource type
		if (c->resource_type!=-1 && c->valid_property(CONDITIONP_ResourceType)) 
			fprintf(out, "\t\t%s:resource(\"%s\") --aka resource(%d)\n",
				condvar, aokutil::get_res_str(c->resource_type), c->resource_type);
		//unit object
		if (c->uid_object!=-1 && c->valid_property(CONDITIONP_UIDObject))
			fprintf(out, "\t\t%s:unit_object(%d)\n", condvar, c->uid_object);
		//unit location
		if (c->uid_location!=-1 && c->valid_property(CONDITIONP_UIDLocation))
			fprintf(out, "\t\t%s:unit_location(%d)\n", condvar, c->uid_location);
		//unit const
		if (c->unit_const!=-1 && c->valid_property(CONDITIONP_UnitConst))
			fprintf(out, "\t\t%s:unit_const(%d)\n", condvar, c->unit_const);
		//player
		if (c->player!=-1 && c->valid_property(CONDITIONP_Player))
			fprintf(out, "\t\t%s:player(%d)\n", condvar, c->player);
		//technology
		if (c->technology!=-1 && c->valid_property(CONDITIONP_Technology))
			fprintf(out, "\t\t%s:technology(%d)\n", condvar, c->technology);
		//timer (uses amount() function in lua)
		if (c->timer!=-1 && c->valid_property(CONDITIONP_Timer))
			fprintf(out, "\t\t%s:amount(%d)\n", condvar, c->timer);
		//area
		if (c->area.ur.x!=-1 && c->area.ll.x!=-1 && c->valid_property(CONDITIONP_Area))  
			fprintf(out, "\t\t%s:area(%d,%d, %d,%d) --(lowerleft, upperright)\n", 
				condvar, c->area.ll.x, c->area.ll.y, c->area.ur.x, c->area.ur.y);
		//unit group
		if (c->unit_group!=-1 && c->valid_property(CONDITIONP_UnitGroup))
			fprintf(out, "\t\t%s:unit_group(\"%s\") --aka unit_group(%d)\n",
				 condvar, aokutil::get_ugroup_str(c->unit_group), c->unit_group); 
		//unit type
		if (c->unit_type!=-1 && c->valid_property(CONDITIONP_UnitType))
			fprintf(out, "\t\t%s:unit_type(\"%s\") --aka unit_type(%d)\n",
				condvar, aokutil::get_utype_str(c->unit_type), c->unit_type);
		//ai signal
		if (c->ai_signal!=-1 && c->valid_property(CONDITIONP_AISignal))
			fprintf(out, "\t\t%s:ai_signal(%d)\n", condvar, c->ai_signal);
	}

	//Effects
	const char *effectvar="effect";
	for (int i=0; i<t->effects.size(); i++)
	{
		Effect *e = t->effects.at(i);

		//comment
		fprintf(out, "\t--Effect %d %s\n", i, e->getName());
		//declaration
		fprintf(out, "\t%s = %s:effect_%s()\n", effectvar, trigvar, e->getName());
		//ai goal
		if (e->ai_goal!=-1 && e->valid_property(EFFECTP_AIGoal))
			fprintf(out, "\t\t%s:ai_goal(%d)\n", effectvar, e->ai_goal);
		//amount
		if (e->amount!=-1 && e->valid_property(EFFECTP_Amount))
			fprintf(out, "\t\t%s:amount(%d)\n", effectvar, e->amount);
		//resource
		if (e->resource!=-1 && e->valid_property(EFFECTP_Resource))
			fprintf(out, "\t\t%s:resource(\"%s\") --aka resource(%d)\n",
				effectvar, aokutil::get_res_str(e->resource), e->resource);
		//diplomacy
		if (e->diplomacy!=-1 && e->valid_property(EFFECTP_Diplomacy))
			fprintf(out, "\t\t%s:diplomacy(\"%s\") --aka diplomacy(%d)\n",
				effectvar, aokutil::get_diplomacy_str(e->diplomacy), e->diplomacy);
		//unit location
		if (e->uid_location!=-1 && e->valid_property(EFFECTP_UIDLocation))
			fprintf(out, "\t\t%s:unit_location(%d)\n", effectvar, e->uid_location);
		//unit const
		if (e->unit_const!=-1 && e->valid_property(EFFECTP_UnitConst))
			fprintf(out, "\t\t%s:unit_const(%d)\n", effectvar, e->unit_const);
		//selected unit(s)
		if (e->num_selected!=-1 && e->valid_property(EFFECTP_UnitConst))
		{
			fprintf(out, "\t\t%s:units(", effectvar);
			for (int i=0; i<e->num_selected; i++)
			{
				fprintf(out, "%d", e->uids[i]);
				if (i<e->num_selected-1) //add comma on all except last
					fprintf(out, ", ");
			}
			fprintf(out, ")\n"); 
		}
		//player_source
		if (e->player_source!=-1 && e->valid_property(EFFECTP_PlayerSource))
			fprintf(out, "\t\t%s:player(%d)\n", effectvar, e->player_source);
		//player_target
		if (e->player_target!=-1 && e->valid_property(EFFECTP_PlayerTarget))
			fprintf(out, "\t\t%s:player_target(%d)\n", effectvar, e->player_target);
		//technology
		if (e->technology!=-1 && e->valid_property(EFFECTP_Technology))
			fprintf(out, "\t\t%s:technology(%d)\n", effectvar, e->technology);
		//display time
		if (e->display_time!=-1 && e->valid_property(EFFECTP_DisplayTime))
			fprintf(out, "\t\t%s:time(%d)\n", effectvar, e->display_time);
		//trigger index
		if (e->trigger_index>=0 && e->valid_property(EFFECTP_TriggerIndex))
			fprintf(out, "\t\t%s:trigger(%d)\n", effectvar, e->trigger_index);
		//location
		if (e->location.x!=-1 && e->valid_property(EFFECTP_Location))
			fprintf(out, "\t\t%s:location(%d,%d)\n", effectvar, e->location.x, e->location.y);
		//area
		if (e->area.ur.x!=-1 && e->area.ll.x!=-1 && e->valid_property(EFFECTP_Area))
			fprintf(out, "\t\t%s:area(%d,%d, %d,%d) --(lowerleft, upperright)\n", 
				effectvar, e->area.ll.x, e->area.ll.y, e->area.ur.x, e->area.ur.y); 
		//unit group
		if (e->unit_group!=-1 && e->valid_property(EFFECTP_UnitGroup))
			fprintf(out, "\t\t%s:unit_group(\"%s\") --aka unit_group(%d)\n",
				 effectvar, aokutil::get_ugroup_str(e->unit_group), e->unit_group); 
		//unit type
		if (e->unit_type!=-1 && e->valid_property(EFFECTP_UnitType))
			fprintf(out, "\t\t%s:unit_type(\"%s\") --aka unit_type(%d)\n",
				effectvar, aokutil::get_utype_str(e->unit_type), e->unit_type); 
		//panel
		if (e->panel!=-1 && e->valid_property(EFFECTP_Panel))
			fprintf(out, "\t\t%s:panel(%d)\n", effectvar, e->panel);
		//text
		if (e->text.length()>1 && e->valid_property(EFFECTP_Text))
			fprintf(out, "\t\t%s:text(\"%s\")\n", effectvar, e->text.c_str());
		//sound
		if (e->sound.length()>1 && e->valid_property(EFFECTP_Sound))
			fprintf(out, "\t\t%s:sound(\"%s\")\n", effectvar, e->sound.c_str());	
	}
	//ending \n for two lines between each trigger
	fprintf(out, "\n"); 

}

LuaFile *LuaFile::current()
{
	return LuaFile::currentLuaFile;
}
