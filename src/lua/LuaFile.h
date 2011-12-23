#ifndef LUATRIG_H_
#define LUATRIG_H_

#include <stdio.h>
#include <vector>
#include "../genie/Trigger.h"

class LuaFile
{
private:
	char *path;

public:
	LuaFile(const char *path, int len);

	//returns errors found
	char *open();
	
	void write(const char *new_path, bool generate_comments);

	//when reading a lua file, the luafunctions have to know which lua file-object is being used currently
	//they call this function to get the correct lua object
	//open() sets currentLuaFile
	static LuaFile *current();
	static LuaFile *currentLuaFile;

	std::vector<Trigger *> triggers;

};

#endif
