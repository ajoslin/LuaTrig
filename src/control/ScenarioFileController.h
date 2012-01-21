#ifndef SCENARIO_FILE_CONTROLLER_H_
#define SCENARIO_FILE_CONTROLLER_H_

#include "FileController.h"

class Scenario; //fwd so we don't have to include here

class ScenarioFileController : public FileController
{
private:
	Scenario *scenario;
public:
	ScenarioFileController();

	void setPath(const char *);
	void write(const char *);
	void write();
	FileError read();

	void copyTriggers(FileController *);
	std::vector<Trigger *> getTriggers();

	const char *getPath();
};

#endif
