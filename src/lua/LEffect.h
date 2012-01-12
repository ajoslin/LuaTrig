#ifndef LEFFECT_H_
#define LEFFECT_H_

#include <stdarg.h>

#include "../genie/Effect.h"

class LEffect
{
	int eId;
	int trigId;

	Effect *effect;
	bool checkParam(EffectProperty p);
	void paramError(EffectProperty p) throw(char *);

public:
	LEffect(Effect *e, int eId, int trigId);

	void location(int x, int y) throw(char *);
	void area(int llX, int llY, int urX, int urY) throw(char *);
	void ai_goal(int goal) throw(char *);
	void amount(int amount) throw(char *);
	void diplomacy(int diplo) throw(char *);
	void diplomacy(const char *diplo) throw(char *);
	void time(int t) throw(char *);
	void panel(int p) throw(char *);
	void player_source(int p) throw(char *);
	void p_source(int p) throw(char *);
	void player_target(int p) throw(char *);
	void p_target(int p) throw(char *);
	void resource(int res) throw(char *);
	void resource(const char *res) throw(char *);
	void technology(int t) throw(char *);
	void tech(int t) throw(char *);
	void trigger(int trig) throw(char *);
	void units(int u1=-1,int u2=-1,int u3=-1,int u4=-1,int u5=-1,int u6=-1,int u7=-1,int u8=-1,int u9=-1,
		int u10=-1,int u11=-1,int u12=-1,int u13=-1,int u14=-1,int u15=-1,int u16=-1,int u17=-1,int u18=-1,
		int u19=-1,int u20=-1,int u21=-1,int u22=-1) throw(char *);
	void unit_location(int uid) throw(char *);
	void unit_group(int ugroup) throw(char *);
	void unit_group(const char *ugroup) throw(char *);
	void unit_type(int utype) throw(char *);
	void unit_type(const char *utype) throw(char *);
	void unit_const(int uconst) throw(char *);
	void text(const char *text) throw(char *);
	void sound(const char *sound) throw(char *);
};





#endif