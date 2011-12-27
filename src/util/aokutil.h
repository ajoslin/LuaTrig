#ifndef AOK_UTIL_H
#define AOK_UTIL_H

class AOKRES
{
public:
	long num;
	char *label;
	AOKRES(long n, const char *l);
};

class aokutil
{
public:
	static const AOKRES resources[14];
	static int get_res_id(char *s);
	static bool is_res_id(int res);
	static const char *get_res_str(int id);

	static const AOKRES unit_types[5];
	static int get_utype(char *s);
	static bool is_utype(int type);
	static const char *get_utype_str(int id);

	static const AOKRES diplomacy[3];
	static int get_diplomacy(char *s);
	static bool is_diplomacy(int d);
	static const char *get_diplomacy_str(int id);

	static const AOKRES unit_groups[54];
	static int get_ugroup(char *s);
	static const char *get_ugroup_str(int id);
};

#endif