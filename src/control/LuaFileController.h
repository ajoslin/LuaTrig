#ifndef LUA_FILE_CONTROLLER_H_
#define LUA_FILE_CONTROLLER_H_

#include "FileController.h"

class LuaFile; //fwd so we don't have to include here

class LuaFileController : public FileController
{
private:
	LuaFile *luaFile;
public:
	LuaFileController();

	void setPath(const char *);
	void write(const char *);
	void write();
	FileError read();

	void copyTriggers(FileController *);
	std::vector<Trigger *> getTriggers();

	const char *getPath();
};

#endif
