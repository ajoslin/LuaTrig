#include "ScenarioFileController.h"
#include "../genie/Scenario.h"

ScenarioFileController::ScenarioFileController()
{
}

void ScenarioFileController::setPath(const char *path)
{
	//whenever resetting the path, delete the old scen that was stored
	delete scenario;
	scenario = new Scenario(path);
}

FileError ScenarioFileController::read()
{
	scenario->open();
	scenario->read();
	scenario->cleanup();
	FileError err;
	return err;
}

//writes scn
void ScenarioFileController::write(const char *writePath)
{
	scenario->write(writePath);
	scenario->cleanup();
}

void ScenarioFileController::write()
{
	write(scenario->getPath().c_str());
}


void ScenarioFileController::copyTriggers(FileController *other)
{
	scenario->triggers = other->getTriggers();
}

std::vector<Trigger *> ScenarioFileController::getTriggers()
{
	return scenario->triggers;
}

const char *ScenarioFileController::getPath()
{
	return scenario->getPath().c_str();
}
