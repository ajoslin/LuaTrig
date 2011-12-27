#ifndef TRIGGER_H_
#define TRIGGER_H_

#include <vector>
#include <string>
#include "Effect.h"
#include "Condition.h"

 
class Trigger
{
public:
	Trigger();

	void read(FILE *scx);
	void write(FILE *out);
	
	const static size_t MAX_TRIGNAME = 128;

	long state;
	long loop;
	char unknown;
	char obj;
	long obj_order;
	std::string description;
	std::string name;

	std::vector<Effect *> effects;
	std::vector<Condition *> conds;
};

#endif