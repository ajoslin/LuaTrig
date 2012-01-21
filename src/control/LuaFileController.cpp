#include "LuaFileController.h"
#include "../lua/LuaFile.h"
#include "../genie/Trigger.h"

LuaFileController::LuaFileController()
{
}

void LuaFileController::setPath(const char *path)
{
	//whenever resetting the path, delete the old luafile that was stored
	delete luaFile;
	luaFile = new LuaFile(path);
}

FileError LuaFileController::read()
{
	bool hasErr = luaFile->read();
	FileError err;
	if (hasErr)
		err.message.assign(luaFile->error());
	
	return err;
}

//writes lua
void LuaFileController::write(const char *writePath)
{
	luaFile->write(writePath);
}

void LuaFileController::write()
{
	write(luaFile->getPath().c_str());
}

void LuaFileController::copyTriggers(FileController *other)
{
	luaFile->triggers = other->getTriggers();
}

std::vector<Trigger *> LuaFileController::getTriggers()
{
	return luaFile->triggers;
}

const char *LuaFileController::getPath()
{
	return luaFile->getPath().c_str();
}
