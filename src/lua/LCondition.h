#ifndef LCONDITION_H_
#define LCONDITION_H_

class Condition; //fwd here so no need to include

class LCondition
{
private:
	Condition *cond;
	void checkParam(int pType) throw(char *);

public:
	LCondition(Condition *c);

	void area(int llX, int llY, int urX, int ury) throw(char *);
	void amount(int amt) throw(char *);
	void resource(int res) throw(char *);
	void unit_object(int uid) throw(char *);
	void unit_location(int uid) throw(char *);
	void player(int p) throw(char *);
	void technology(int tech) throw(char *);
	void timer(int time) throw(char *);
	void unit_group(int group) throw(char *);
	void unit_group(const char *group) throw(char *);
	void unit_type(int type) throw(char *);
	void unit_type(const char *type) throw(char *);
	void unit_const(int uconst) throw(char *);
	void ai_signal(int signal) throw(char *);
};

#endif
