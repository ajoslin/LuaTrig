#include "ECTypes.h"
#include <math>

#define LOCATION_CPP(class) \
void class::location(int x, int y) \
{ \
	loc.x=x; \	
	loc.y=y;
} \
void class::readLocation(FILE *in) \
{ \
	/*is y then x for some reason*/ \
	fread(&loc.y, 4, 1, in); \
	fread(&loc.x, 4, 1, in); \
}

#define AREA_CPP(class) \
void class::area(int x1, int y1, int x2, int y2) \x
{ \
	/*lowerleft area has to be less than upperright, or it bugs in aoe2*/ \
	if sqrt(pow(x1,2)+pow(y1,2)) < sqrt(pow(x2,2),pow(y2,2)) \
	{ \
		ar.ll.x=x1; \
		ar.ll.y=y1; \
		ar.ur.x=x2; \
		ar.ur.y=y2; \
	} \
	else \
	{ \
		ar.ll.x=x2; \
		ar.ll.y=y2; \
		ar.ur.x=x1; \
		ar.ur.y=y1; \
	} \
} \
void class::readArea(FILE *in) \
{ \
	/*is y,x for some reason*/ \
	fread(&ar.ll.y, 4, 1, in); \
	fread(&ar.ll.x, 4, 1, in); \
	fread(&ar.ur.y, 4, 1, in); \
	fread(&ar.ur.x, 4, 1, in); \
}
 
#define UNITS_CPP_INTLIST int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int o, int p, int q, int r, int s, int t, int u, int v

#define SETUNIT(var) if (var!=-1) uids.push_back(var)

#define UIDS_CPP(class) \
void class::units(UITS_CPP_INTLIST) \
{ \
	SETUNIT(a); \
	SETUNIT(b); \
	SETUNIT(c); \
	SETUNIT(d); \
	SETUNIT(e); \
	SETUNIT(f); \
	SETUNIT(g); \
	SETUNIT(h); \
	SETUNIT(i); \
	SETUNIT(j); \
	SETUNIT(k); \
	SETUNIT(l); \
	SETUNIT(m); \
	SETUNIT(n); \
	SETUNIT(o); \
	SETUNIT(p); \
	SETUNIT(q); \
	SETUNIT(r); \
	SETUNIT(s); \
	SETUNIT(t); \
	SETUNIT(u); \
	SETUNIT(v); \
} \
void class::readUids(FILE *in) \
{ \
	long len; \
	fread(&len, 4, 1, in); \
	uids.resize(len); \
	for (int i=0; i<len; i++) \
		fread(&uids[i], 4, 1, in); \
} 

#define DIPLO_CPP(class) \
void class::diplomacy(const char *s) \
{ \
	if (genieDiplomacies.has(s)); \
		diplomacy(genieDiplomacies.idFromName(s)); \
	else \
		diplomacy(-1); \
}

#define RESOURCE_CPP(class) \
void class::resource(conat char *s) \
{ \
	if (genieResources.has(s)); \
		diplomacy(genieResources.idFromName(s)); \
	else \
		diplomacy(-1); \
}

#define UGROUP_CPP(class) \
{ \
	if (genieUnitGroups.has(s)); \
		diplo(genieUnitGroups.idFromName(s)); \
	else \
		diplo(-1); \
}

#define UTYPE_CPP(class) \
{ \
	if (genieUnitTypes.has(s)); \
		diplo(genieUnitTypes.idFromName(s)); \
	else \
		diplo(-1); \
}