#ifndef LCONDITION_H_
#define LCONDITION_H_

#include "../genie/Condition.h"

class LCondition
{
private:
	int cId;
	int trigId;

	Condition *cond;
	bool checkParam(ConditionProperty p);
	void paramError(ConditionProperty p) throw(char *);

public:
	LCondition(Condition *c, int cId, int trigId);

	void area(int llX, int llY, int urX, int ury) throw(char *);
	void amount(int amt) throw(char *);
	void resource(int res) throw(char *);
	void resource(const char *res) throw(char *);
	void unit_object(int uid) throw(char *);
	void unit_location(int uid) throw(char *);
	void player(int p) throw(char *);
	void technology(int tech) throw(char *);
	void tech(int tech) throw(char *);
	void timer(int time) throw(char *);
	void unit_group(int group) throw(char *);
	void unit_group(const char *group) throw(char *);
	void unit_type(int utype) throw(char *);
	void unit_type(const char *utype) throw(char *);
	void unit_const(int uconst) throw(char *);
	void ai_signal(int signal) throw(char *);
};

#endif
