#ifndef LUATRIG_H_
#define LUATRIG_H_

#include <stdio.h>
#include <vector>
#include <string>

class lua_State; //fwd it here so we don't have to include
class Trigger;

class LuaFile
{
private:
	char *path;
	std::string read_error;

	void writeTrigger(FILE *out, int id);

public:
	LuaFile(const char *path, int len);

	//returns whether has errors
	bool read();

	//returns error str from last read, or null
	const char *error();
	
	void write(const char *new_path);

	bool add_trigger(Trigger *t, int id);

	//when reading a lua file, the luafunctions have to know which lua file-object is being used currently
	//they call this function to get the correct lua object
	//open() sets currentLuaFile
	static LuaFile *current();
	static LuaFile *currentLuaFile;

	std::vector<Trigger *> triggers;

};

#endif
