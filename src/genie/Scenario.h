#ifndef SCENARIO_H_
#define SCENARIO_H_

#include <vector>
#include "Trigger.h"

class Scenario
{
private:
	const char *path;

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
	bool read(bool save_triggers);
	bool write(const char *new_path);

	void cleanup();

	std::vector<Trigger *> triggers;

	long numtriggers;
};

#endif