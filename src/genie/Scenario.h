#ifndef SCENARIO_H_
#define SCENARIO_H_

#include "Trigger.h"
#include <string>
#include <vector>

class Scenario
{
private:
	std::string path;

	int skiptotriggers(const char *path);
	int skiptoscenarioend(const char *path);

	long trigger_start;
	long trigger_end;
	long scenario_end;

	unsigned long headerlength;

public:	
	Scenario(const char *path);
	~Scenario();

	bool open();
	bool read(bool save_triggers = true);
	bool write(const char *new_path);

	std::string getPath() { return path; };

	void cleanup();

	std::vector<Trigger *> triggers;
};

#endif



