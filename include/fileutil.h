#ifndef FILE_UTIL_H
#define FILE_UTIL_H

/**
	Taken from AOKTS:
	zlibfile.h -- Deflation/Inflation of DEFLATE streams to a FILE.
	Written by DiGiT for AOKTS and zlibnoh utilities.
	Contact: cyan.spam@gmail.com

	These files (zlibfile.h and zlibfile.cpp) may be freely distributed as long as the above notice remains intact.

	UTIL
**/

#include <zlib.h>	//for the zlib errors & types
#include <stdio.h>

#define SKIP(file, bytes) for (int i=0; i<bytes; i++) fgetc(file); \
	bytes_read+=bytes
#define READ(var, size, num, file) fread(var, size, num, file); \
	bytes_read+=(size*num)

extern "C" int fsize(const char *path);

extern "C" int deflate_file(Bytef *in, int length, FILE *out);

extern "C" int inflate_file(Bytef *in, int length, FILE *out);

#endif