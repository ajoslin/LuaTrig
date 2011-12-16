#ifndef LUATRIG_H_
#define LUATRIG_H_

#include <stdio.h>
#include "Trigger.h"

class lua_State;
class Scenario; //just forward it here so don't have to include the whole scenario.h

#define MAX_TRIGGERS 500

class LuaTrig
{
private:
	LuaTrig();
	static LuaTrig *my_instance;

	//Stores current scn and lua state
	Scenario *scn;
	lua_State *lua;

public:
	static LuaTrig *instance();

	std::list<Trigger *> triggers;
	Trigger *get_trigger(int id);

	void init_lua();
	bool read_lua(const char *path);
	void write_lua(const char *path);
	void close_lua();

	bool open_scn(const char *path);
	void read_scn(bool save_triggers);
	void write_scn(const char *basepath, const char *newpath);

	void cleanup_scn_files();
};

#endif
