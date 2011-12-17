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

const char *readline(FILE *f, int skip)
{
	std::string s;
	s.resize(300); //big buffer

	for (int i=0; i<skip; i++) fgetc(f);

	int len=0;
	while (len<300) //max 300 lines readable
	{
		char c=fgetc(f);
		if (c=='\n' || c==EOF) break;
		s[len++]=c;
	}
	s.resize(len+1); //take down to size + nullchar
	return s.c_str();
}

}	//end C