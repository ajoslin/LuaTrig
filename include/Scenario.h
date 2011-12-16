#ifndef SCENARIO_H_
#define SCENARIO_H_

//PERL_BUFF: Defines the size of the output buffer used by zlib.
//Note: This must be limited for deflation or AOK can't read the compressed file.
#define PERL_BUFF 0x2000

#include "Trigger.h"
#include "my_util.h"
#include "LuaTrig.h"

class Scenario
{
public:
	~Scenario();

	bool open(const char *path);
	bool read(bool save_triggers);
	bool write(const char *base_scx_path, const char *new_scx_path);

	void cleanup();

private:
	int skiptotriggers(const char *path);
	int skiptoscenarioend(const char *path);

	long trigger_start;
	long trigger_end;
	long scenario_end;


	unsigned long headerlength;
};

#endif