/* MODEL */

#include "Trigger.h"
#include "util_file.h"

Trigger::Trigger()
{
	state = loop = unknown = obj = obj_order = 0;
}


void Trigger::read(FILE *scx)
{
	fread(&state, sizeof(long), 1, scx);
	fread(&loop, sizeof(long), 1, scx);
	fread(&unknown, sizeof(char), 1, scx);
	fread(&obj, sizeof(char), 1, scx);
	fread(&obj_order, sizeof(long), 1, scx);
	
	//skip zeroes data (4 bytes)
	fskip(scx, 4);

	description=readstr(scx);
	name=readstr(scx);
	
	//Effects
	long effect_count;
	fread(&effect_count, sizeof(long), 1, scx);

	//printf("\tReading Effects: effect_count=%d\n", effect_count);

	std::vector<Effect *> new_effects;
	long nextECType;
	for (int i=0; i<effect_count; i++)
	{
		//effect type
		fread(&nextECType, 4, 1, scx);

		//printf("\t--[Effect %d]: Type %d, \"%s\"\n", i, nextECType, Effect::types[nextECType]);
		
		Effect *e=Effect::createType(nextECType);
		e->read(scx);
		new_effects.push_back(e);
	}
	effects = new_effects;

	//skip effect_count longs representing effect order
	//this order doesn't matter, is only display order and not execution order
	fskip(scx, 4*effect_count);
	
	//Conditions
	long condition_count;
	fread(&condition_count, sizeof(long), 1, scx);

	//printf("\tReading Conditions: cond_count=%d\n", condition_count);
	
	std::vector<Condition *> new_conds;
	for (int i=0; i<condition_count; i++)
	{
		//cond type
		fread(&nextECType, 4, 1, scx);

		//printf("\t--[Cond %d]: Type %d, \"%s\"\n", i, nextECType, Condition::types[nextECType]);

		Condition *c=Condition::createType(nextECType);
		c->read(scx);
		new_conds.push_back(c);
	}
	conds = new_conds;

	//skip condition order, condition_count longs
	fskip(scx, 4*condition_count);
}

void Trigger::write(FILE *scx)
{
	fwrite(&state, 4, 1, scx);
	fwrite(&loop, 4, 1, scx);
	fwrite(&unknown, 1, 1, scx);
	fwrite(&obj, 1, 1, scx);
	fwrite(&obj_order, 4, 1, scx);

	for (int i=0; i<4; i++) putc(0, scx); //4 zeroes

	int len;

	len = description.length();
	fwrite(&len, sizeof(long), 1, scx);
	fwrite(description.c_str(), sizeof(char), len, scx);

	len = name.length();
	fwrite(&len, sizeof(long), 1, scx);
	fwrite(name.c_str(), sizeof(char), len, scx);

	//Effects
	len = effects.size();
	fwrite(&len, 4, 1, scx);

	for (int i=0; i<effects.size(); i++)
		effects[i]->write(scx);
	//effect order
	for (int i = 0; i < len; i++)
		fwrite(&i, 4, 1, scx);

	//Conditions
	len = conds.size();
	fwrite(&len, 4, 1, scx);

	for (int i=0; i<conds.size(); i++)
		conds[i]->write(scx);

	for (int i = 0; i < len; i++)
		fwrite(&i, 4, 1, scx);
}

