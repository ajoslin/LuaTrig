/* MODEL */

#include "Trigger.h"

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
	for (int i=0; i<4; i++) fgetc(scx);

	long desclen;
	fread(&desclen, sizeof(long), 1, scx); 
	description.resize(desclen);
	for (int i=0; i<desclen; i++) {
		char c=description.at(i);
		fread(&c, sizeof(char), 1, scx);
	}
	//description.at(desclen)='\0'; //make sure it's null terminated

	long namelen;
	fread(&namelen, sizeof(long), 1, scx); 
	name.resize(namelen);
	for (int i=0; i<namelen; i++) {
		char c=name.at(i);
		fread(&c, sizeof(char), 1, scx);
	}
	//name.at(namelen)='\0'; //make sure it's null terminated
	
	//Effects
	long effect_count;
	fread(&effect_count, sizeof(long), 1, scx);

	effects.clear();
	for (int i=0; i<effect_count; i++)
	{
		Effect *e=new Effect;
		e->read(scx);
		effects.push_back(e);
	}
	//skip effect_count longs representing effect order
	//this order doesn't matter, is only display order and not execution order
	for (int i=0; i<4*effect_count; i++) fgetc(scx);
	
	//Conditions
	long condition_count;
	fread(&condition_count, sizeof(long), 1, scx);
	
	conds.clear();
	for (int i=0; i<condition_count; i++)
	{
		Condition *c=new Condition;
		c->read(scx);
		conds.push_back(c);
	}
	//skip condition order, condition_count longs
	for (int i=0; i<4*condition_count; i++) fgetc(scx);
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