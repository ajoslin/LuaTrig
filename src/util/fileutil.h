#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#include <string>
#include <stdio.h>
#include <zlib.h>	//for the zlib errors & types

/**
	Taken from AOKTS:
	zlibfile.h -- Deflation/Inflation of DEFLATE streams to a FILE.
	Written by DiGiT for AOKTS and zlibnoh utilities.
	Contact: cyan.spam@gmail.com

	These files (zlibfile.h and zlibfile.cpp) may be freely distributed as long as the above notice remains intact.

	UTIL
**/

#define SKIP(file, bytes) for (int i=0; i<bytes; i++) fgetc(file); \
	bytes_read+=bytes
#define READ(var, size, num, file) fread(var, size, num, file); \
	bytes_read+=(size*num)

extern "C" int fsize(const char *path);

extern "C" const char *readline(FILE *f, int skip);

/*
	deflate_file: Deflates a string of characters and outputs to a file.

	unsigned char *in: The input string.
	int length: The length of the input string.
	FILE *out: DEFLATEd output filestream.

	returns: zlib error codes
*/
extern "C" int deflate_file(Bytef *in, int length, FILE *out);

/*
	inflate_file: Inflates a string of characters and outputs to a file.

	unsigned char *in: The input string.
	int length: The length of the output string.
	FILE *out: DEFLATEd output filestream.

	returns: zlib error codes
*/
extern "C" int inflate_file(Bytef *in, int length, FILE *out);


#endif