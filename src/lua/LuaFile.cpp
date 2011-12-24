
#include "LuaFile.h"
#include "LuaTrigger.h"
#include "LuaEffect.h"
#include "LuaCondition.h"
#include <lua.hpp>

LuaFile *LuaFile::currentLuaFile = NULL;

LuaFile::LuaFile(const char *_path, int len)
{
	path = new char[len+1];
	for (int i=0; i<len; i++)
		path[i] = _path[i];
	path[len+1]='\0';

	read_error=NULL;
}

bool LuaFile::read()
{
	currentLuaFile = this;

	lua_State *L = lua_open();
	// load the libs
	luaL_openlibs(L);

	LuaEffect::lua_init(L);
	LuaCondition::lua_init(L);
	LuaTrigger::lua_init(L);

	triggers.clear();
	
	//Record error if it exists
	int has_errors=luaL_dofile(L, path);

	if (read_error!=NULL) //free error if it was occupied before
		free(read_error);

	if (has_errors!=0)
	{
		read_error=(char *)lua_tostring(L, -1);
		lua_pop(L, 1); // remove error message
	}
	else
	{
		read_error=NULL;
	}
	
	lua_close(L);
	return has_errors!=0;
};

const char *LuaFile::error()
{
	return (const char *)read_error;
}

void LuaFile::write(const char *new_path, bool generate_comments=false)
{
	FILE *out = fopen(new_path, "w");
	for (int i=0; i<triggers.size(); i++)
		triggers[i]->writetolua(out, i, generate_comments);
	fclose(out);
}

LuaFile *LuaFile::current()
{
	return LuaFile::currentLuaFile;
}
