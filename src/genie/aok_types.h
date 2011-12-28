#ifndef AOK_TYPES_H_
#define AOK_TYPES_H_

#include <utility>
#include <string>
#include <string.h>

#define PAIR_DNE_ID 	-99
#define PAIR_DNE_STR	"__DNE"
#define RESOURCES_LEN 	14
#define DIPLO_LEN 		3
#define UTYPES_LEN 		5
#define UGROUPS_LEN 	54


/**
 	AOKPT AND AOKRECT taken from: AOK Trigger Studio

	DiGiT: AOK points are y,x apparently (or at least the way I'm seeing them).
*/
class AOKPT
{
public:
	long y, x;

	AOKPT(long yy = -1, long xx = -1)
		: y(yy), x(xx)
	{
	}
};

class AOKRECT
{
public:
	AOKPT ll;
	AOKPT ur;
	AOKRECT(long ll_y=-1, long ll_x=-1, long ur_y=-1, long ur_x=-1)
		: ll(ll_y, ll_x), ur(ur_y, ur_y)
	{
	}
};

class GeniePair 
{
public:
	GeniePair(int i, const char *n) { id=i; name.assign(n); };

	bool equals(int i) const { return i==id; };
	bool equals(const char *n) const { return strcmp(name.c_str(), n)==0; };

	std::string name;
	int id;
};

class GeniePairGroup
{
private:
	GeniePair *pairs;
	int len;
public:
	GeniePairGroup(GeniePair pairs[], int len);

	bool has(int id);
	bool has(const char *n);

	int idFromName(const char *n);
	const char *nameFromId(int id);
};

extern GeniePair res_array[RESOURCES_LEN];
extern GeniePairGroup *genieResources;

extern GeniePair diplo_array[DIPLO_LEN];
extern GeniePairGroup *genieDiplomacies;

extern GeniePair utype_array[UTYPES_LEN];
extern GeniePairGroup *genieUnitTypes;

extern GeniePair ugroup_array[UGROUPS_LEN];
extern GeniePairGroup *genieUnitGroups;

#endif