/* MODEL */

#include "../include/Trigger.h"

Trigger::Trigger()
{
	state = loop = unknown = obj = obj_order = 0;
}

Trigger::Trigger(int i)
{
	state = loop = unknown = obj = obj_order = 0;
	index = i;
	name = "Trigger ";
	name+=i;
}


int Trigger::readfromscx(FILE *scx)
{
	long bytes_read = 0;

	READ(&state, sizeof(long), 1, scx);
	READ(&loop, sizeof(long), 1, scx);
	READ(&unknown, sizeof(char), 1, scx);
	READ(&obj, sizeof(char), 1, scx);
	READ(&obj_order, sizeof(long), 1, scx);
	
	//skip zeroes data (4 bytes)
	SKIP(scx, 4);

	long desclen;
	READ(&desclen, sizeof(long), 1, scx); 
	description.resize(desclen);
	for (int i=0; i<desclen; i++) {
		char c=description.at(i);
		READ(&c, sizeof(char), 1, scx);
	}
	//description.at(desclen)='\0'; //make sure it's null terminated

	long namelen;
	READ(&namelen, sizeof(long), 1, scx); 
	name.resize(namelen);
	for (int i=0; i<namelen; i++) {
		char c=name.at(i);
		READ(&c, sizeof(char), 1, scx);
	}
	//name.at(namelen)='\0'; //make sure it's null terminated
	
	//Effects
	long effect_count;
	READ(&effect_count, sizeof(long), 1, scx);
	
	if (effect_count>0)
	{
		effects.clear();
		for (int i=0; i<effect_count; i++)
		{
			Effect *e = new Effect;
			bytes_read += e->readfromscx(scx);
			effects.push_back(e);
		}
		SKIP(scx, 4*effect_count); //skip effect_count longs representing effect order. 
		//this order doesn't matter, is only display order and not execution order
	}

	//Conditions
	long condition_count;
	READ(&condition_count, sizeof(long), 1, scx);
	
	if (condition_count>0)
	{
		conds.clear();
		for (int i=0; i<condition_count; i++)
		{
			Condition *c = new Condition;
			bytes_read += c->readfromscx(scx);
			conds.push_back(c);
		}
		SKIP(scx, 4*condition_count); //skip condition_count longs representing effect order. 
	}

	return bytes_read;
}

void Trigger::writetoscx(FILE *scx)
{
	fwrite(&state, 4, 1, scx);
	fwrite(&loop, 4, 1, scx);
	fwrite(&unknown, 1, 1, scx);
	fwrite(&obj, 1, 1, scx);
	fwrite(&obj_order, 4, 1, scx);

	for (int i=0; i<4; i++) putc(0, scx); //zeroes

	int len;

	//+1 for the null char at end
	len = description.length();
	fwrite(&len, sizeof(long), 1, scx);
	fwrite(description.c_str(), sizeof(char), len, scx);

	len = name.length();
	fwrite(&len, sizeof(long), 1, scx);
	fwrite(name.c_str(), sizeof(char), len, scx);

	//Effects
	len = effects.size();
	fwrite(&len, 4, 1, scx);

	list<Effect *>::iterator eff_it;
	for (eff_it=effects.begin(); eff_it!=effects.end(); eff_it++)
		(*eff_it)->writetoscx(scx);
	//effect order
	for (int i = 0; i < len; i++)
		fwrite(&i, 4, 1, scx);

	//Conditions
	len = conds.size();
	fwrite(&len, 4, 1, scx);

	list<Condition *>::iterator cond_it;
	for (cond_it=conds.begin(); cond_it!=conds.end(); cond_it++)
		(*cond_it)->writetoscx(scx);

	for (int i = 0; i < len; i++)
		fwrite(&i, 4, 1, scx);
}

void Trigger::writetolua(FILE *out, int id, bool easyread=true)
{
	char *trigvar = new char[15];
	sprintf(trigvar, "trigger_%d", id);

	//Trigger header with comment if easyread is on
	if (easyread)
		fprintf(out, "----- TRIGGER %d -----\n", id);
	fprintf(out, "local %s = Trigger(%d)\n", trigvar, id);
	//name (always write)
	fprintf(out, "\t%s:name(\"%s\")\n", trigvar, name.c_str());
	//description (always write)
	fprintf(out, "\t%s:description(\"%s\")\n", trigvar, description.c_str());
	//on
	fprintf(out, "\t%s:on(%s)\n", trigvar, state ? "true" : "false");
	//loop
	fprintf(out, "\t%s:loop(%s)\n", trigvar, loop ? "true" : "false");
	//objective
	if (obj)
		fprintf(out, "\t%s:objective(%s)\n", trigvar, obj ? "true" : "false");
	//objective order
	if (obj || obj_order)
		fprintf(out, "\t%s:desc_order(%d)\n", trigvar, obj_order);
	
	int i;
	//Conditions
	list<Condition *>::iterator cond_it=conds.begin();
	i=0;
	char *ecvar = new char[15];
	while (cond_it!=conds.end())
	{
		sprintf(ecvar, "condition_%d", i);
		//comment if easyread
		if (easyread)
			fprintf(out, "\t-- CONDITION %d %s --\n", i, (*cond_it)->getName().c_str());
		(*cond_it)->writetolua(out, trigvar, ecvar);
		cond_it++;
		i++;
	}

	//Effects
	list<Effect *>::iterator eff_it=effects.begin();
	i=0;
	while (eff_it!=effects.end())
	{
		sprintf(ecvar, "effect_%d", i);
		//comment if easyread
		if (easyread)
			fprintf(out, "\t-- EFFECT %d %s --\n", i, (*eff_it)->getName().c_str());
		(*eff_it)->writetolua(out, trigvar, ecvar);
		eff_it++;
		i++;
	}

}