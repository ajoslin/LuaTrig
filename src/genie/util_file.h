#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include <zlib.h>	//for the zlib errors & types
#include <stdio.h>
#include <string>

/**
	zlibfile.h -- Deflation/Inflation of DEFLATE streams to a FILE.
	Written by DiGiT for AOKTS and zlibnoh utilities.
	Contact: cyan.spam@gmail.com

	These files (zlibfile.h and zlibfile.cpp) may be freely distributed as long as the above notice remains intact.
**/

int readstr(FILE *in, std::string str);

extern "C" int fskip(FILE *f, int bytes);

//Note from andy: all three of these functions are written by DiGiT

extern "C" int fsize(const char *path);

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