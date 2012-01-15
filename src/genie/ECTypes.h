#ifndef ECTYPES_H_
#define ECTYPES_H_

//defines for all the various effect/cond types.
//these are all macros because they all get re-used pretty often


//max 22 units sel. listed here because swig variable args support is bad.
//to get around this we just list 22 ints, with all but 1 optional.
//messy, but easier for the lua user; he doesn't have to write a table.
#define UNITS_H_INTLIST int a, int b=-1, int c=-1, int d=-1, int e=-1, int f=-1, int g=-1, int h=-1, int i=-1, int j=-1, int k=-1, int l=-1, int m=-1, int o=-1, int p=-1, int q=-1, int r=-1, int s=-1, int t=-1, int u=-1, int v=-1

//All the var declarations for effects and conditions
//effect stuff (shares some things with conds)
#define AMOUNT_H_FIELD 		long amt
#define LOCATION_H_FIELD 	AOKPT loc
#define AREA_H_FIELD		AOKRECT ar
#define AIGOAL_H_FIELD		long aigoal
#define DIPLO_H_FIELD		long diplo
#define DISPTIME_H_FIELD	long disptime
#define PANEL_H_FIELD		long pan
#define PSOURCE_H_FIELD		long pl_source
#define PTARGET_H_FIELD		long pl_target;
#define RESOURCE_H_FIELD	long res
#define TECH_H_FIELD		long tec
#define TRIGGER_H_FIELD		long trig
#define UIDS_H_FIELD		std::vector<int> uids
#define UIDLOC_H_FIELD		long uloc
#define UGROUP_H_FIELD		long ugroup
#define UTYPE_H_FIELD		long utype
#define UCONST_H_FIELD		long uconst
#define SOUND_H_FIELD		std::string snd
#define TEXT_H_FIELD		std::string txt
//cond only stuff
#define TIMER_H_FIELD		long tim;
#define AISIGNAL_H_FIELD	long aisignal;
#define UIDOBJECT_H_FIELD	long uid_obj;
#define PLAYER_H_FIELD		long pl;


//all the function declarations for various effect and condition properties.
//effect funcs first (many shared with conditions)
#define AMOUNT_H_FUNC \
	void amount(int a) { amt=a; }; \
	virtual long getAmount() { return amt; }; \
	void readAmount(FILE *in) { fread(&amt, 4, 1, in); }

#define LOCATION_H_FUNC \
 	void location(int x, int y); \
 	virtual AOKPT getLocation() { return loc; }; \
 	void readLocation(FILE *in)

#define AREA_H_FUNC \
	void area(int, int, int, int); \
	virtual AOKRECT getArea() { return ar; };
	void readArea(FILE *in)

#define AIGOAL_H_FUNC \
	void ai_goal(int g) { aigoal=g; }; \
	virtual long getAiGoal() { return aigoal; }; \
	void readAiGoal(FILE *in) { fread(&aigoal, 4, 1, in); }

#define DIPLO_H_FUNC \
	void diplomacy(int d) { diplo=d; }; \
	void diplomacy(const char *); \
	virtual long getDiplomacy() { return diplo; }; \
	void readDiplomacy(FILE *in) { fread(&diplo, 4, 1, in); }

#define DISPTIME_H_FUNC \
	void display_time(int d) { disptime=d; }; \
	virtual long getDisplayTime() { return disptime; }; \
	void readDisplayTime(FILE *in) { fread(&disptime, 4, 1, in); }

#define PANEL_H_FUNC \
	void panel(int p) { pan=p }; \
	virtual long getPanel() { return pan; }; \
	void readPanel(FILE *in) { fread(&pan, 4, 1, in); }

#define PSOURCE_H_FUNC \
	void p_source(int p) { pl_source=p; }; \
	virtual long getPlayerSource() { return pl_source; }; \
	void readPlayerSource(FILE *in) { fread(&pl_source, 4, 1, in); }

#define PTARGET_H_FUNC \
	void p_target(int p) { pl_target=p; }; \
	virtual long getPlayerTarget() { return pl_target; }; \
	void readPlayerTarget(FILE *in) { fread(&pl_target, 4, 1, in); }

#define RESOURCE_H_FUNC \
	void resource(int r) { res=r; }; \
	void resource(const char *); \
	virtual long getResource() { return res; }; \
	void readResource(FILE *in) { fread(&res, 4, 1, in); }

#define TECH_H_FUNC \
	void technology(int t) { tech=t; }; \
	void tech(int t) { technology(t); }; \
	virtual long getTechnology() { return tec; }; \
	void readTechnology(FILE *in) { fread(&tec, 4, 1, in); }

#define TRIGGER_H_FUNC \
	void trigger(int t) { trig=t; }; \
	virtual long getTrigger() { return trig; }; \
	void readTrigger(FILE *in) { (fread(&trig, 4, 1, in); }

#define UIDS_H_FUNC \
	void units(UNITS_H_INTLIST); \
	virtual std::vector<int> getUids() { return uids; }; \
	void readUids(FILE *in)

#define UIDLOC_H_FUNC \
	void uid_location(int u) { uloc=u; }; \
	virtual long getUidLocation() { return uloc; }; \
	void readUidLocation(FILE *in) { fread(&uloc, 4, 1, in); }

#define UGROUP_H_FUNC \
	void unit_group(int u) { ugroup=u; }; \
	void unit_group(const char *); \
	virtual long getUnitGroup() { return ugroup; }; \
	void readUnitGroup(FILE *in) { fread(&ugroup, 4, 1, in); }

#define UTYPE_H_FUNC \
	void unit_type(int u) { utype=u; }; \
	void unit_type(const char *); \
	virtual long getUnitType() { return utype; }; \
	void readUnitType(FILE *in) { fread(&utype, 4, 1, in); }

#define UCONST_H_FUNC \
	void unit_const(int u) { uconst=u; }; \
	virtual long getUnitConst() { return uconst; }; \
	void readUnitConst(FILE *in) { fread(&uconst, 4, 1, in); }

#define SOUND_H_FUNC \
	void sound(const char *s) { snd.assign(s) }; \
	virtual std::string getSound() { return snd; }; \
	void readSound(FILE *in) { readstr(in, snd); }

#define TEXT_H_FUNC \
	void text(const char *t) { txt.assign(t) }; \
	virtual std::string getText() { return txt; }; \
	void readText(FILE *in) { readstr(in, txt); }

//condition only funcs
#define TIMER_H_FUNC \
	void time(int t) { tim=t; }; \
	void amount(int t) { time(t) }; /*let the lua user write either amount() or time() (to make it easier on him)*/ \
	virtual long getTimer() { return tim; }; \
	void readTimer(FILE *in) { fread(&tim, 4, 1, in); }

#define AISIGNAL_H_FUNC \
	void ai_signal(int s) { aisignal=s; }; \
	virtual long getAiSignal() { return aisignal; }; \
	void readAiSignal(FILE *in) { fread(&aisignal, 4, 1, in); }

#define UIDOBJECT_H_FUNC \
	void uid_object(int u) { uid_obj=u; }; \
	virtual long getUidObject() { return uid_obj; }; \
	void readUidObject(FILE *in) { fread(&uid_obj, 4, 1, in); }

#define PLAYER_H_FUNC \
	void player(int p) { pl=p; }; \
	virtual long getPlayer() { return pl; }; \
	void readPlayer(FILE *in) { fread(&pl, 4, 1, in); }

#endif