#ifndef LUATRIG_H_
#define LUATRIG_H_

#include <stdio.h>
#include <vector>
#include <string>

class lua_State; //fwd these here so we don't have to include
class Trigger;

class LuaFile
{
private:
	std::string path;
	std::string read_error;

	void writeTrigger(FILE *out, int id);
	void writeLuaString(FILE *out, const char *str);

public:
	LuaFile(const char *path);

	//returns whether has errors
	bool read();
	const char *error(); //returns error str from last read, or null
	void write(const char *new_path);
	
	bool add_trigger(Trigger *t, int id);

	std::string getPath() { return path; };

	//when reading a lua file, the luafunctions have to know which lua file-object is being used currently
	//they call this function to get the correct lua object
	//open() sets currentLuaFile
	static LuaFile *current();
	static LuaFile *currentLuaFile;

	std::vector<Trigger *> triggers;

};

#endif



