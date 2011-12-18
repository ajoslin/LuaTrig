#include "aokutil.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
 

char *stringtolower(char *s)
{
	char *s2=(char *)calloc(strlen(s), sizeof(char));
	for (int i=0; i<strlen(s); i++)
		*(s2+i)=(char)tolower(*(s+i));
	*(s2+strlen(s))='\0';
	return s2;
}
		

AOKRES::AOKRES(long n, const char *l)
{
	label=(char *)calloc(strlen(l)+1, sizeof(char));
	for (int i=0; i<strlen(l); i++)
		*(label+i)=(char)tolower(*(l+i));
	*(label+strlen(l))='\0';
	num=n;
}

const struct AOKRES aokutil::resources[] =
{
	AOKRES(0, "Food"),
	AOKRES(1, "Wood"),
	AOKRES(2, "Stone"),
	AOKRES(3, "Gold"),
	AOKRES(4, "Population Limit"),
	AOKRES(7, "Relics"),
	AOKRES(11, "Population"),
	AOKRES(20, "Kills"),
	AOKRES(21, "Technologies"),
	AOKRES(37, "Villager Population"),
	AOKRES(40, "Military Population"),
	AOKRES(41, "Conversions"),
	AOKRES(43, "Razings"),
	AOKRES(44, "Kill Ratio"),
};

int aokutil::get_res_id(char *s)
{
	char *s2=stringtolower(s);
	int i;
	for (i=0; i<14; i++)
		if (strcmp(s2, resources[i].label)==0)
			return resources[i].num;
	
	return -1;
}

bool aokutil::is_res_id(int res)
{
	for (int i=0; i<14; i++)
		if (resources[i].num==res)
			return true;
	return false;
}

const char *aokutil::get_res_str(int id)
{
	for (int i=0; i<14; i++)
		if (id==resources[i].num)
			return resources[i].label;
	return NULL;
}






const struct AOKRES aokutil::unit_types[] =
{
	AOKRES(-1, "None"),
	AOKRES(1, "Other"),
	AOKRES(2, "Building"),
	AOKRES(3, "Civilian"),
	AOKRES(4, "Military"),
};

int aokutil::get_utype(char *s)
{
	char *s2=stringtolower(s);
	for (int i=0; i<5; i++) {
		if (strcmp(s2, unit_types[i].label)==0) 
			return resources[i].num;
	}
	return -2;
}

bool aokutil::is_utype(int type)
{
	for (int i=0; i<5; i++) 
		if (unit_types[i].num==type)
			return true;
	return false;
}

const char *aokutil::get_utype_str(int id)
{
	for (int i=0; i<5; i++)
		if (id==unit_types[i].num)
			return unit_types[i].label;
	return NULL;
}







const struct AOKRES aokutil::diplomacy[] =
{
	AOKRES(0, "Ally"),
	AOKRES(1, "Neutral"),
	AOKRES(2, "Enemy"),
};

int aokutil::get_diplomacy(char *s)
{
	char *s2=stringtolower(s);
	for (int i=0; i<3; i++)
		if (strcmp(s2, diplomacy[i].label)==0) 
			return diplomacy[i].num;
	
	return -1;
}

bool aokutil::is_diplomacy(int d)
{
	for (int i=0; i<3; i++) 
		if (diplomacy[i].num==d)
			return true;
	return false;
}

const char *aokutil::get_diplomacy_str(int id)
{
	for (int i=0; i<3; i++)
		if (id==diplomacy[i].num)
			return diplomacy[i].label;
	return NULL;
}







const struct AOKRES aokutil::unit_groups[] =
{
	AOKRES(0x00, "Archer"),
	AOKRES(0x01, "Artifact"),
	AOKRES(0x02, "Trade Boat"),
	AOKRES(0x03, "Building"),
	AOKRES(0x04, "Civilian"),
	AOKRES(0x05, "Sea Fish"),
	AOKRES(0x06, "Soldier"),
	AOKRES(0x07, "Berry Bush"),
	AOKRES(0x08, "Stone Mine"),
	AOKRES(0x09, "Prey Animal"),
	AOKRES(0x0A, "Predator Animal"),
	AOKRES(0x0B, "Other"),
	AOKRES(0x0C, "Cavalry"),
	AOKRES(0x0D, "Siege Weapon"),
	AOKRES(0x0E, "Map Decoration"),
	AOKRES(0x0F, "Tree"),
	AOKRES(0x12, "Priest"),
	AOKRES(0x13, "Trade Cart"),
	AOKRES(0x14, "Transport Boat"),
	AOKRES(0x15, "Fishing Boat"),
	AOKRES(0x16, "War Boat"),
	AOKRES(0x17, "Conquistador"),
	AOKRES(0x1B, "Walls"),
	AOKRES(0x1C, "Phalanx"),
	AOKRES(0x1E, "Flags"),
	AOKRES(0x20, "Gold Mine"),
	AOKRES(0x21, "Shore Fish"),
	AOKRES(0x22, "Cliff"),
	AOKRES(0x23, "Petard"),
	AOKRES(0x24, "Cavalry Archer"),
	AOKRES(0x25, "Dolphin"),
	AOKRES(0x26, "Birds"),	//only FLDOG, lol
	AOKRES(0x27, "Gates"),
	AOKRES(0x28, "Piles"),
	AOKRES(0x29, "Resource"),
	AOKRES(0x2A, "Relic"),
	AOKRES(0x2B, "Monk with Relic"),
	AOKRES(0x2C, "Hand Cannoneer"),
	AOKRES(0x2D, "Two-Handed Swordsman"),
	AOKRES(0x2E, "Pikeman"),
	AOKRES(0x2F, "Scout Cavalry"),
	AOKRES(0x30, "Ore Mine"),
	AOKRES(0x31, "Farm"),
	AOKRES(0x32, "Spearman"),
	AOKRES(0x33, "Packed Siege Units"),
	AOKRES(0x34, "Tower"),
	AOKRES(0x35, "Boarding Boat"),
	AOKRES(0x36, "Unpacked Siege Units"),
	AOKRES(0x37, "Scorpion"),
	AOKRES(0x38, "Raider"),
	AOKRES(0x39, "Cavalry Raider"),
	AOKRES(0x3A, "Sheep"),
	AOKRES(0x3B, "King"),	//doesn't include King?
	AOKRES(0x3D, "Horse")
};

int aokutil::get_ugroup(char *s)
{
	char *s2=stringtolower(s);
	for (int i=0; i<54; i++)
		if (strcmp(unit_groups[i].label, s2)==0)
			return unit_groups[i].num;
	
	return -1;
}

const char *aokutil::get_ugroup_str(int id)
{
	for (int i=0; i<54; i++)
		if (id==unit_groups[i].num)
			return unit_groups[i].label;
	return NULL;
}