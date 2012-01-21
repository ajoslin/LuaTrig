#ifndef LUATRIGCONTRL_H_
#define LUATRIGCONTRL_H_

#include <string>
#include <vector>

class Trigger;

struct FileError
{
	std::string message;
};

class FileController
{
public:
	virtual void setPath(const char *)=0;
	virtual void write(const char *)=0;
	virtual void write()=0;
	virtual FileError read()=0;

	virtual void copyTriggers(FileController *)=0;
	virtual std::vector<Trigger *> getTriggers()=0;

	virtual const char *getPath()=0;
};

#endif
