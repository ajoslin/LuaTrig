#ifndef AOK_DATA_H_
#define AOK_DATA_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define pf(s) printf("%s. %d bytes read\n", s, bytes_read)
#define pf2(s, v) printf(s, v); pf("")
#define pf3(s, v, w) printf(s, v, w); pf("")

#define SKIP(file, bytes) for (int i=0; i<bytes; i++) fgetc(file); \
	bytes_read+=bytes
#define READ(var, size, num, file) fread(var, size, num, file); \
	bytes_read+=(size*num)

class AOKRES
{
public:
	long num;
	char *label;
	AOKRES(long n, const char *l);
};

/*	AOK points are y,x apparently (or at least the way
	I'm seeing them). */
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

class my_util
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

	static int fsize(const char *path);
};

#endif