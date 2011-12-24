#ifndef LUATRIG_H_
#define LUATRIG_H_

#include <stdio.h>
#include <vector>
#include "../genie/Trigger.h"

class LuaFile
{
private:
	char *path;
	char *read_error;

public:
	LuaFile(const char *path, int len);

	//returns whether has errors
	bool read();

	//returns error str from last read, or null
	const char *error();
	
	void write(const char *new_path, bool generate_comments);

	//when reading a lua file, the luafunctions have to know which lua file-object is being used currently
	//they call this function to get the correct lua object
	//open() sets currentLuaFile
	static LuaFile *current();
	static LuaFile *currentLuaFile;

	std::vector<Trigger *> triggers;

};

#endif
