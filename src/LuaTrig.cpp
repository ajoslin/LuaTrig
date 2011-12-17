
#include "../include/LuaTrig.h"
#include "../include/Scenario.h"
#include <lua.hpp>
//#include <luabind/luabind.hpp>

LuaTrig *LuaTrig::my_instance = NULL;

LuaTrig::LuaTrig()
{
	scn = NULL;
	lua = NULL;
}

LuaTrig *LuaTrig::instance()
{
	if (!my_instance)
		my_instance = new LuaTrig();
	return my_instance;
}

Trigger *LuaTrig::get_trigger(int trigid)
{
	list<Trigger *>::iterator it;
	if (trigid <= triggers.size()/2) //if in first half of list, start at begin
	{
		it=triggers.begin();
		for (int i=0; i<trigid; i++) 
			it++;
	}
	else //if in second half of list, start at end
	{
		it=triggers.end();
		for (int i=triggers.size(); i>trigid; i--) 
			it--;
	}
	return *it;
}


/**
 * Lua Stuff
 */
void LuaTrig::init_lua()
{
	lua_State *L = lua_open();

	// load the libs
	luaL_openlibs(L);

	this->lua=L;
}

bool LuaTrig::read_lua(const char *path)
{
	//clear trigger list, we're reading a new list
	triggers.clear();
	int haserrors=luaL_dofile(lua, path);
	if (haserrors)
	{
		printf("-- %s\n", lua_tostring(lua, -1));
		lua_pop(lua, 1); // remove error message
	}
	return !haserrors;
}

void LuaTrig::write_lua(const char *path)
{
	FILE *out=fopen(path, "w");

	list<Trigger *>::iterator it = triggers.begin();
	int i=0;
	while (it!=triggers.end())
	{
		(*it)->writetolua(out, i++, true);
		it++;
	}

	fclose(out);
}

void LuaTrig::close_lua()
{
	lua_close(lua);
	this->lua=NULL;
}

/**
 * Scenario stuff
 */
bool LuaTrig::open_scn(const char *path)
{
	if (scn)
		delete scn;
	
	scn = new Scenario();

	return scn->open(path);
}

void LuaTrig::read_scn(bool save_triggers)
{
	scn->read(save_triggers);
}

void LuaTrig::write_scn(const char *basepath, const char *newpath)
{
	scn->write(basepath, newpath);
}

void LuaTrig::cleanup_scn_files()
{
	scn->cleanup();
}
