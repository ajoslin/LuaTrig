#ifndef TRIGGER_H_
#define TRIGGER_H_

#include <list>
#include <algorithm>
#include <string>
using namespace std;
#include "Effect.h"
#include "Condition.h"
#include "my_util.h"


/* Triggers */
class Trigger
{
public:
	Trigger();
	Trigger(int id);

	int readfromscx(FILE *scx);
	void writetoscx(FILE *out);
	void writetolua(FILE *out, int id, bool easyread);
	
	const static size_t MAX_TRIGNAME = 128;

	long state, loop;
	char unknown, obj;
	long obj_order;
	string description;
	string name;

	int index; //index in scenario

	/*	get_player: Returns non-GAIA player for conditions/effect in the trigger.

		Returns:
		* 0 if all players are unassigned (GAIA)
		* -1 if there is a mix of non-GAIA players
		* EC player index if above are false
	*/
	int get_player();

	std::list<Effect *> effects;
	std::list<Condition *> conds;
};

#endif