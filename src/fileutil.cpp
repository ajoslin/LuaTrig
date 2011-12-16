#include "../include/fileutil.h"

//PERL_BUFF: Defines the size of the output buffer used by zlib.
//Note: This must be limited for deflation or AOK can't read the compressed file.
#define PERL_BUFF 0x2000

/* Functions */

extern "C"
{

int fsize(const char *path) 
{
	FILE *f=fopen(path, "rb");
	fseek(f, 0, SEEK_END);
	long size = ftell(f); 
	fclose(f);
	return size;
}

}	//end C