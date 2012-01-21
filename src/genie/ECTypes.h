//defines for all the various effect/cond types.
//these are all macros because they all get re-used pretty often


//max 22 units sel. listed here because swig variable args support is bad.
//to get around this we just list 22 ints, with all but 1 optional.
//messy, but easier for the lua user; he doesn't have to write a table.
#define UNITS_H_INTLIST int a, int b=-1, int c=-1, int d=-1, int e=-1, int f=-1, int g=-1, int h=-1, int i=-1, int j=-1, int k=-1, int l=-1, int m=-1, int n=-1, int o=-1, int p=-1, int q=-1, int r=-1, int s=-1, int t=-1, int u=-1, int v=-1

//All the var declarations for effects and conditions
//effect stuff (shares some things with conds)
#define AMOUNT_H_FIELD 		eclong amt
#define LOCATION_H_FIELD 	AOKPT loc
#define AREA_H_FIELD		AOKRECT ar
#define AIGOAL_H_FIELD		eclong aigoal
#define DIPLO_H_FIELD		eclong diplo
#define DISPTIME_H_FIELD	eclong disptime
#define PANEL_H_FIELD		eclong pan
#define PSOURCE_H_FIELD		eclong pl_source
#define PTARGET_H_FIELD		eclong pl_target;
#define RESOURCE_H_FIELD	eclong res
#define TECH_H_FIELD		eclong tec
#define TRIGGER_H_FIELD		eclong trig
#define UIDS_H_FIELD		std::vector<int> uids
#define UIDLOC_H_FIELD		eclong uloc
#define UGROUP_H_FIELD		eclong ugroup
#define UTYPE_H_FIELD		eclong utype
#define UCONST_H_FIELD		eclong uconst
#define SOUND_H_FIELD		std::string snd
#define TEXT_H_FIELD		std::string txt
//cond only stuff
#define TIMER_H_FIELD		eclong tim
#define AISIGNAL_H_FIELD	eclong aisignal
#define UIDOBJECT_H_FIELD	eclong uid_obj
#define PLAYER_H_FIELD		eclong pl


//all the function declarations for various effect and condition properties.
//effect funcs first (many shared with conditions)
#define AMOUNT_H_FUNC \
	void amount(int a) { amt.set(a); } \
	long getAmount() { return amt.get(); } \
	void readAmount(FILE *in) { fread(&amt, 4, 1, in); }

#define LOCATION_H_FUNC \
 	void location(int x, int y); \
 	AOKPT getLocation() { return loc; } \
 	void readLocation(FILE *in)

#define AREA_H_FUNC \
	void area(int, int, int, int); \
	AOKRECT getArea() { return ar; } \
	void readArea(FILE *in)

#define AIGOAL_H_FUNC \
	void ai_goal(int g) { aigoal.set(g); } \
	long getAiGoal() { return aigoal.get(); } \
	void readAiGoal(FILE *in) { fread(&aigoal, 4, 1, in); }

#define DIPLO_H_FUNC \
	void diplomacy(int d) { diplo.set(d); } \
	void diplomacy(const char * s); \
	long getDiplomacy() { return diplo.get(); } \
	void readDiplomacy(FILE *in) { fread(&diplo, 4, 1, in); }

#define DISPTIME_H_FUNC \
	void display_time(int d) { disptime.set(d); } \
	void time(int d) { display_time(d); } \
	long getDisplayTime() { return disptime.get(); } \
	void readDisplayTime(FILE *in) { fread(&disptime, 4, 1, in); }

#define PANEL_H_FUNC \
	void panel(int p) { pan.set(p); } \
	long getPanel() { return pan.get(); } \
	void readPanel(FILE *in) { fread(&pan, 4, 1, in); }

#define PSOURCE_H_FUNC \
	void p_source(int p) { pl_source.set(p); } \
	long getPlayerSource() { return pl_source.get(); } \
	void readPlayerSource(FILE *in) { fread(&pl_source, 4, 1, in); }

#define PTARGET_H_FUNC \
	void p_target(int p) { pl_target.set(p); } \
	long getPlayerTarget() { return pl_target.get(); } \
	void readPlayerTarget(FILE *in) { fread(&pl_target, 4, 1, in); }

#define RESOURCE_H_FUNC \
	void resource(int r) { res.set(r); } \
	void resource(const char *); \
	long getResource() { return res.get(); } \
	void readResource(FILE *in) { fread(&res, 4, 1, in); }

#define TECH_H_FUNC \
	void technology(int t) { tec.set(t); } \
	void tech(int t) { technology(t); } \
	long getTechnology() { return tec.get(); } \
	void readTechnology(FILE *in) { fread(&tec, 4, 1, in); }

#define TRIGGER_H_FUNC \
	void trigger(int t) { trig.set(t); } \
	long getTriggerIndex() { return trig.get(); } \
	void readTriggerIndex(FILE *in) { fread(&trig, 4, 1, in); }

#define UIDS_H_FUNC \
	void units(UNITS_H_INTLIST); \
	std::vector<int> getUids() { return uids; } \
	void readUids(FILE *in, long len)

#define UIDLOC_H_FUNC \
	void unit_location(int u) { uloc.set(u); } \
	void uid_location(int u) { unit_location(u); } \
	long getUidLocation() { return uloc.get(); } \
	void readUidLocation(FILE *in) { fread(&uloc, 4, 1, in); }

#define UGROUP_H_FUNC \
	void unit_group(int u) { ugroup.set(u); } \
	void unit_group(const char *); \
	long getUnitGroup() { return ugroup.get(); } \
	void readUnitGroup(FILE *in) { fread(&ugroup, 4, 1, in); }

#define UTYPE_H_FUNC \
	void unit_type(int u) { utype.set(u); } \
	void unit_type(const char *); \
	long getUnitType() { return utype.get(); } \
	void readUnitType(FILE *in) { fread(&utype, 4, 1, in); }

#define UCONST_H_FUNC \
	void unit_const(int u) { uconst.set(u); } \
	long getUnitConst() { return uconst.get(); } \
	void readUnitConst(FILE *in) { fread(&uconst, 4, 1, in); }

#define SOUND_H_FUNC \
	void sound(const char *s) { snd=s; } \
	std::string getSound() { return snd; } \
	void readSound(FILE *in) { snd=readstr(in); }

#define TEXT_H_FUNC \
	void text(const char *t) { txt=t; } \
	std::string getText() { return txt; } \
	void readText(FILE *in) { txt=readstr(in); }

//condition only funcs
#define TIMER_H_FUNC \
	void time(int t) { tim.set(t); } \
	void amount(int t) { time(t); } /*let the lua user write either amount() or time() (to make it easier on him)*/ \
	long getTimer() { return tim.get(); } \
	void readTimer(FILE *in) { fread(&tim, 4, 1, in); }

#define AISIGNAL_H_FUNC \
	void ai_signal(int s) { aisignal.set(s); } \
	long getAiSignal() { return aisignal.get(); } \
	void readAiSignal(FILE *in) { fread(&aisignal, 4, 1, in); }

#define UIDOBJECT_H_FUNC \
	void unit_object(int u) { uid_obj.set(u); } \
	void uid_object(int u) { unit_object(u); } \
	long getUidObject() { return uid_obj.get(); } \
	void readUidObject(FILE *in) { fread(&uid_obj, 4, 1, in); }

#define PLAYER_H_FUNC \
	void player(int p) { pl.set(p); } \
	long getPlayer() { return pl.get(); } \
	void readPlayer(FILE *in) { fread(&pl, 4, 1, in); } 



