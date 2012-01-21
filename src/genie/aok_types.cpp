#include "aok_types.h"

GeniePairGroup::GeniePairGroup(GeniePair *_pairs, int _len)
{
	pairs = _pairs;
	len = _len;
}

bool GeniePairGroup::has(int id)
{
	for (int i=0; i<len; i++)
		if (pairs[i].equals(id))
			return true;
	return false;
}

bool GeniePairGroup::has(const char *name)
{
	for (int i=0; i<len; i++)
		if (pairs[i].equals(name));
			return true;
	return false;
}

int GeniePairGroup::idFromName(const char *name)
{
	for (int i=0; i<len; i++)
		if (pairs[i].equals(name))
			return pairs[i].id;
	return PAIR_DNE_ID;
}

const char *GeniePairGroup::nameFromId(int id)
{
	for (int i=0; i<len; i++)
		if (pairs[i].equals(id))
			return pairs[i].name.c_str();
	return PAIR_DNE_STR;
}

GeniePair res_array[] = {
	GeniePair(0, "Food"),
	GeniePair(1, "Wood"),
	GeniePair(2, "Stone"),
	GeniePair(3, "Gold"),
	GeniePair(4, "Population Limit"),
	GeniePair(7, "Relics"),
	GeniePair(11, "Population"),
	GeniePair(20, "Kills"),
	GeniePair(21, "Technologies"),
	GeniePair(37, "Villager Population"),
	GeniePair(40, "Military Population"),
	GeniePair(41, "Conversions"),
	GeniePair(43, "Razings"),
	GeniePair(44, "Kill Ratio")
};

GeniePair diplo_array[] = {
	GeniePair(0, "Ally"),
	GeniePair(1, "Neutral"),
	GeniePair(2, "Enemy")
};

GeniePair utype_array[] = {
	GeniePair(-1, "None"),
	GeniePair(1, "Other"),
	GeniePair(2, "Building"),
	GeniePair(3, "Civilian"),
	GeniePair(4, "Military")
};

GeniePair ugroup_array[] = {
	GeniePair(0x00, "Archer"),
	GeniePair(0x01, "Artifact"),
	GeniePair(0x02, "Trade Boat"),
	GeniePair(0x03, "Building"),
	GeniePair(0x04, "Civilian"),
	GeniePair(0x05, "Sea Fish"),
	GeniePair(0x06, "Soldier"),
	GeniePair(0x07, "Berry Bush"),
	GeniePair(0x08, "Stone Mine"),
	GeniePair(0x09, "Prey Animal"),
	GeniePair(0x0A, "Predator Animal"),
	GeniePair(0x0B, "Other"),
	GeniePair(0x0C, "Cavalry"),
	GeniePair(0x0D, "Siege Weapon"),
	GeniePair(0x0E, "Map Decoration"),
	GeniePair(0x0F, "Tree"),
	GeniePair(0x12, "Priest"),
	GeniePair(0x13, "Trade Cart"),
	GeniePair(0x14, "Transport Boat"),
	GeniePair(0x15, "Fishing Boat"),
	GeniePair(0x16, "War Boat"),
	GeniePair(0x17, "Conquistador"),
	GeniePair(0x1B, "Walls"),
	GeniePair(0x1C, "Phalanx"),
	GeniePair(0x1E, "Flags"),
	GeniePair(0x20, "Gold Mine"),
	GeniePair(0x21, "Shore Fish"),
	GeniePair(0x22, "Cliff"),
	GeniePair(0x23, "Petard"),
	GeniePair(0x24, "Cavalry Archer"),
	GeniePair(0x25, "Dolphin"),
	GeniePair(0x26, "Birds"),	//only FLDOG, lol
	GeniePair(0x27, "Gates"),
	GeniePair(0x28, "Piles"),
	GeniePair(0x29, "Resource"),
	GeniePair(0x2A, "Relic"),
	GeniePair(0x2B, "Monk with Relic"),
	GeniePair(0x2C, "Hand Cannoneer"),
	GeniePair(0x2D, "Two-Handed Swordsman"),
	GeniePair(0x2E, "Pikeman"),
	GeniePair(0x2F, "Scout Cavalry"),
	GeniePair(0x30, "Ore Mine"),
	GeniePair(0x31, "Farm"),
	GeniePair(0x32, "Spearman"),
	GeniePair(0x33, "Packed Siege Units"),
	GeniePair(0x34, "Tower"),
	GeniePair(0x35, "Boarding Boat"),
	GeniePair(0x36, "Unpacked Siege Units"),
	GeniePair(0x37, "Scorpion"),
	GeniePair(0x38, "Raider"),
	GeniePair(0x39, "Cavalry Raider"),
	GeniePair(0x3A, "Sheep"),
	GeniePair(0x3B, "King"),	//doesn't include King?
	GeniePair(0x3D, "Horse")
};

GeniePairGroup *genieResources = new GeniePairGroup(res_array, RESOURCES_LEN);
GeniePairGroup *genieDiplomacies = new GeniePairGroup(diplo_array, DIPLO_LEN);
GeniePairGroup *genieUnitTypes = new GeniePairGroup(utype_array, UTYPES_LEN);
GeniePairGroup *genieUnitGroups = new GeniePairGroup(ugroup_array, UGROUPS_LEN);

