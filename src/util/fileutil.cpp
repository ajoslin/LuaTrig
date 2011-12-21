#include "fileutil.h"

//PERL_BUFF: Defines the size of the output buffer used by zlib.
//Note: This must be limited for deflation or AOK can't read the compressed file.
#define PERL_BUFF 0x2000

/* Functions */

extern "C"
{

int deflate_file(Bytef *in, int length, FILE *out)
{
	z_stream strm;	//see zlib.h
	Bytef compressed[PERL_BUFF];	//This holds our compressed data until we write it.
	int code;	//holds return values from zlib functions

// Initialize the stream

	strm.zalloc = (alloc_func)Z_NULL;
	strm.zfree = (free_func)Z_NULL;
	strm.next_in = in;
	strm.avail_in = length;

	code = deflateInit2(&strm, -1, Z_DEFLATED, -15, 9, Z_DEFAULT_STRATEGY);

// Deflate it

	while (code == Z_OK)
	{
		strm.next_out = compressed;
		strm.avail_out = PERL_BUFF;
		code = deflate(&strm, Z_FINISH);
		if (code == Z_OK || code == Z_STREAM_END)
			fwrite(compressed, sizeof(Bytef), PERL_BUFF - strm.avail_out, out);
	}

// Cleanup & Return

	deflateEnd(&strm);

	return code;
}

int inflate_file(Bytef *in, int length, FILE *out)
{
	z_stream strm;
	Bytef uncompressed[PERL_BUFF];	//buffer for decompressed data
	int code;	//return from zlib funcs

// Initialize the stream

	strm.zalloc = (alloc_func)Z_NULL;
	strm.zfree = (free_func)Z_NULL;
	strm.next_in = in;
	strm.avail_in = length;
	strm.avail_out = 0;	//for the while condition check, not necessary
	code = inflateInit2(&strm, -15);

//	inflate it

	while (code == Z_OK && strm.avail_out == 0)
	{
		strm.next_out = uncompressed;
		strm.avail_out = sizeof(uncompressed);
		code = inflate(&strm, Z_SYNC_FLUSH);
		switch (code)
		{
		case Z_OK:
			fwrite(uncompressed, sizeof(Bytef),
				sizeof(uncompressed),	//assume uncompressed is full, so write it all
				out);
			break;
		case Z_STREAM_END:
			fwrite(uncompressed, sizeof(Bytef),
				sizeof(uncompressed) - strm.avail_out,	//can't assume that now
				out);
			break;
		}
	}

	printf("inflate_file wrote %d bytes.\n", strm.total_out);

//	Cleanup & Return

	inflateEnd(&strm);

	return code;
}

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