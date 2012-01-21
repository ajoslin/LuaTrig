#include "Scenario.h"
#include "util_file.h"

#define SKIP(file, bytes) for (int i=0; i<bytes; i++) fgetc(file); \
	bytes_read+=bytes

#define READ(readin, typelen, len, file) fread(readin, typelen, len, file); \
	bytes_read+=typelen*len

Scenario::Scenario(const char *path)
{
	this->path.assign(path);
}

Scenario::~Scenario()
{
	cleanup();
}

/**
* IO STUFF
*/
void Scenario::cleanup()
{
	remove("compressed_in.hex");
	remove("scndata.hex");
	remove("header.hex");
	remove("compressed_out.hex");
	remove("out.hex");
	remove("scripts/out.hex");
}

bool Scenario::open()
{
	printf("[O] Opening scenario %s\n", path.c_str());

	FILE *scx = fopen(path.c_str(), "rb");
	if (scx==NULL)
		return false;

	long scx_filesize = fsize(path.c_str());

	long bytes_read = 0;

	char *headerversion= new char[4];
	READ(&headerversion, sizeof(char), 4, scx); //READ macro adds to bytes_read

	READ(&headerlength, sizeof(unsigned long), 1, scx);

	//read geader
	char *header = new char[headerlength];
	READ(header, 1, headerlength, scx);

	FILE *headerfile = fopen("header.hex", "wb");
	fseek(scx, 0, SEEK_SET);
	for (int i=0; i<headerlength+8; i++)
		fputc(fgetc(scx), headerfile);
	fclose(headerfile);


	printf("\t[O] headerlength: %d\n", headerlength);

	printf("\t[O] bytes_read: %d\n", bytes_read);

	//COMPRESSED DATA
	//get length of compressed data
	long clen = scx_filesize - bytes_read;

	printf("\t[O] scx_filesize: %d\n", scx_filesize);
	printf("\t[O] clen: %d\n", clen);

	Bytef *cdata = new Bytef[clen];
	READ(cdata, sizeof(char), clen, scx);

	FILE *out = fopen("scndata.hex", "wb");

	inflate_file(cdata, clen, out);

	fclose(scx);
	fclose(out);

	printf("\t[O] End open\n");

	return true;
}

bool Scenario::read(bool save_triggers)
{
	printf("[R] Reading scenario\n");

	FILE *scx=fopen("scndata.hex", "rb");
	if (scx==NULL)
		return false; //must open scn before reading data

	
	trigger_start = skiptotriggers("scndata.hex");

	long bytes_read = 0;
	SKIP(scx, trigger_start);
	
	int numtriggers;
	READ(&numtriggers, sizeof(long), 1, scx);

	printf("\t[R] numtriggers=%d\n",numtriggers);
	
	long trigger_skip=0;
	bool displayed=0;

	std::vector<Trigger *> scen_triggers;
	for (int i=0; i<numtriggers; i++)
	{
		//printf("[R] TRIGGER %d\n", i);
		Trigger *t = new Trigger;
		t->read(scx);
		scen_triggers.push_back(t);
		//printf("[R] END TRIGGER %d. triggerskip=%d\n", i, ftell(scx)-bytes_read);
	}
	if (save_triggers)
		triggers = scen_triggers;
	
	printf("\t[R] Done reading triggers\n");
	
	trigger_skip = ftell(scx) - bytes_read;
	bytes_read+=trigger_skip;

	//at the end is numtriggers longs representing order of triggers.
	//skip them. they're just the display order, not execution order
	SKIP(scx, 4*numtriggers);

	trigger_end = bytes_read;

	scenario_end = skiptoscenarioend("scndata.hex");

	long filesize=fsize("scndata.hex");
	printf("\t[R] trigger start=%d, trigger end=%d\n", trigger_start, trigger_end);
	printf("\t[R] scenario_end=%d\n", scenario_end);
	printf("\t[R] scndata.hex size: %d, size without triggers: %d\n", filesize, filesize-trigger_skip-4*numtriggers-4);

	printf("\t[R] Read done\n");

	fclose(scx);

	return true;
}

bool Scenario::write(const char *new_path)
{
	printf("[W] Writing scenario %s to %s\n", path.c_str(), new_path);

	//open creates header.hex and scndata.hex
	int success=open();
	if (!success) return false;

	printf("\t[W] Open successful\n");

	//read sets trigger_start and trigger_end, but don't write triggers
	read(false);
	
	//prepare to write uncompressed new scn data to out.hex
	FILE *newdata = fopen("out.hex", "wb");
	long len;

	//write before triggers data
	FILE *olddata = fopen("scndata.hex", "rb");
	len=trigger_start;
	while(len--)
		fputc(fgetc(olddata), newdata);
	fclose(olddata);

	printf("\t[W] wrote trigger_start=%d bytes of pre-triggers data\n", trigger_start);

	//write trigger count
	long numtriggers = triggers.size();
	fwrite(&numtriggers, sizeof(long), 1, newdata);

	printf("\t[W] numtriggers=%d. fpos=%d\n", numtriggers, ftell(newdata));	

	//write triggers
	for (int i=0; i<numtriggers; i++) 
		triggers.at(i)->write(newdata);

	//write trigger order
	for (int i=0; i<numtriggers; i++)
		fwrite(&i, sizeof(long), 1, newdata);
	
	printf("\t[W] wrote triggers. fpos=%d, triggerbytes=%d\n", ftell(newdata), ftell(newdata)-trigger_start-4);
		
	//write after triggers data
	olddata = fopen("scndata.hex", "rb");

	//skip to trigger_end
	for (int i=0; i<trigger_end; i++) fgetc(olddata);

	long restlen=scenario_end-trigger_end;
	//write the rest
	for (int i=0; i<restlen; i++)
		fputc(fgetc(olddata), newdata);
	fclose(olddata);

	printf("\t[W] wrote after triggers data. len=%d\n", restlen);

	//close and reopen newdata, then write it to a byte array
	fclose(newdata);
	newdata = fopen("out.hex", "rb");
	long newdata_len = fsize("out.hex");

	Bytef *uncompr_data = new Bytef[newdata_len];
	fread(uncompr_data, sizeof(char), newdata_len, newdata);	

	printf("\t[W] Wrote new data, out.hex, to byte array. size: %d\n", newdata_len);

	//open new scx file
	FILE *scx=fopen(new_path, "wb");

	//Write header to new scx
	FILE *header=fopen("header.hex", "rb");
	long headerlen=fsize("header.hex");
	for (long i=0; i<headerlen; i++) 
		fputc(fgetc(header), scx);
	fclose(header);

	printf("\t[W] headerlen: %d\n", headerlen);

	//compress new data and write it to new scx
	deflate_file(uncompr_data, newdata_len, scx);

	//done!
	fclose(scx);
	printf("\t[W] Write done!\n");
	
	return true;
}

int Scenario::skiptotriggers(const char *filepath)
{

	long scx_filesize=fsize(filepath);

	FILE *scx = fopen(filepath, "rb");

	long bytes_read=0;
	//skip 4433 bytes - size of CHeader until scn filename
	SKIP(scx, 4433);
	
	//generic len variables for skipping stuff
	short lenshort;
	long lenlong;

	//name
	READ(&lenshort, sizeof(short), 1, scx);
	SKIP(scx, lenshort+24); //24 empty bytes follow namelen
	
	//instructions
	READ(&lenshort, sizeof(short), 1, scx);
	SKIP(scx, lenshort);
	
	//hints
	READ(&lenshort, sizeof(short), 1, scx);
	SKIP(scx, lenshort);
	
	//victory
	READ(&lenshort, sizeof(short), 1, scx);
	SKIP(scx, lenshort);
	
	//defeat
	READ(&lenshort, sizeof(short), 1, scx);
	SKIP(scx, lenshort);
	
	//history
	READ(&lenshort, sizeof(short), 1, scx);
	SKIP(scx, lenshort);
	
	//scouts
	READ(&lenshort, sizeof(short), 1, scx);
	SKIP(scx, lenshort);
	
	//pg_cinem
	READ(&lenshort, sizeof(short), 1, scx);
	SKIP(scx, lenshort);
	
	//vict_cinem
	READ(&lenshort, sizeof(short), 1, scx);
	SKIP(scx, lenshort);

	//lost_cinem
	READ(&lenshort, sizeof(short), 1, scx);
	SKIP(scx, lenshort);
	
	//background_cinem
	READ(&lenshort, sizeof(short), 1, scx);
	SKIP(scx, lenshort);

	//get whether has bmp bool (4byte long) about whether has bmp
	long hasbmp;
	READ(&hasbmp, sizeof(long), 1, scx);

	//skip two more longs, sizex and sizey of bmp
	SKIP(scx, sizeof(long)*2);

	//skip 2 bytes of unknown data
	SKIP(scx, sizeof(char)*2);

	//skip bmp stuff if it exists
	if (hasbmp)
	{
		//bitmap header and misc stuff
		SKIP(scx, 20);

		//bmp size long
		long bmplen;
		READ(&bmplen, sizeof(long), 1, scx);

		//skip the rest of the header (16) and the 1024 byte palette and bmp size
		SKIP(scx, 16+1024+bmplen);
	}

	//skip 32 unknowns
	for (int i=0; i<32; i++)
	{
		READ(&lenshort, sizeof(short), 1, scx);
		SKIP(scx, lenshort);
	}

	//skip 16 ai names
	for (int i=0; i<16; i++)
	{
		READ(&lenshort, sizeof(short), 1, scx);
		SKIP(scx, sizeof(char)*lenshort);
	}

	//skip 16 actual ai files
	for (int i=0; i<16; i++)
	{
		SKIP(scx, 8); //2 null strings
		READ(&lenlong, sizeof(long), 1, scx);
		SKIP(scx, lenlong);
	}
	
	//skip 16 ai type bytes
	SKIP(scx, 16);

	//skip 4 byte seperator
	SKIP(scx, 4);

	//Skip resources for all 16 players
	for (int i=0; i<16; i++)
	{
		//gold, wood, food, stone, porex - 5 longs
		SKIP(scx, sizeof(long)*5); 
		//a random null long
		SKIP(scx, sizeof(long));
	}	
	
	//Victory type
	//4 byte seperator
	SKIP(scx, 4);
	//conquest
	SKIP(scx, 4);
	//zeros1
	SKIP(scx, 4);
	//relics
	SKIP(scx, 4);
	//zeros2
	SKIP(scx, 4);
	//explored
	SKIP(scx, 4);
	//zeros3
	SKIP(scx, 4);
	//BOOL all
	SKIP(scx, 4);
	
	//Mode, score, time
	SKIP(scx, 12);
	
	//Diplomacy
	//16x16 longs
	int diplo=0;
	for (int i=0; i<16; i++)
	{
		for (int j=0; j<16; j++)
		{
			SKIP(scx, sizeof(long));
		}
	}

	//Skip 11520 bytes
	SKIP(scx, 11520);
	//4byte seperator
	SKIP(scx, 4);

	//16 long allied victories
	SKIP(scx, 64);
	
	//Techs
	//num_d techs - 16 longs
	SKIP(scx, 64);
	//disabled techs - 16x30 longs
	SKIP(scx, 64*30);
	//num_d units - 16 longs
	SKIP(scx, 64);
	//disabled units - 16x30 longs
	SKIP(scx, 64*30);
	//num_d buildings - 16 longs
	SKIP(scx, 64);
	//disabled units - 16x20 longs
	SKIP(scx, 64*20);
	//2 null longs
	SKIP(scx, 8);
	//long alltechs
	SKIP(scx, 4);

	//Starting age: 16 longs
	for (int i=0; i<16; i++)
	{
		SKIP(scx, 4);
	}

	//Map
	//4 byte seperator
	SKIP(scx, 4);

	//camera pos - 2 longs
	SKIP(scx, 8);

	//long aitype
	SKIP(scx, 4);

	//map x,y size
	long mapx, mapy;
	READ(&mapx, sizeof(long), 1, scx);
	READ(&mapy, sizeof(long), 1, scx);
	//Terrain: x*y*3 size - (ID,elevation,null) - each 1 byte - at each coord
	SKIP(scx, mapx*mapy*3);


	//Units
	//number of players
	long numplayers;
	READ(&numplayers, sizeof(long), 1, scx);

	//playerdata part 4 for 8 of the players
	//resources
	//read 6 floats for each res and poplimit float (7*4)
	for (int i=0; i<8; i++)
	{
		SKIP(scx, 28);
	}

	//units data
	//players 0-8
	for (int i=0; i<=8; i++)
	{
		long count;
		READ(&count, sizeof(long), 1, scx);
		//Units
		for (int j=0; j<count; j++)
		{
			float xpos, ypos;
			READ(&xpos, sizeof(float), 1, scx);
			READ(&ypos, sizeof(float), 1, scx);
			//who knows
			SKIP(scx, 4);
			//long unitid
			SKIP(scx, 4);
			//some short const
			SKIP(scx, sizeof(short));
			//unknown byte
			SKIP(scx, 1);
			//rotation
			float rotation;
			READ(&rotation, sizeof(float), 1, scx);
			//short frame
			short frame;
			READ(&frame, sizeof(short), 1, scx);
			//long garrison
			long garrison;
			READ(&garrison, sizeof(long), 1, scx);
			//pf2("reading unit %d", unitid);
		}
	}

	//4byte seperator
	SKIP(scx, 4);

	//player data 3
	for (int i=0; i<8; i++)
	{
		//length
		short len;
		READ(&len, sizeof(short), 1, scx);
		//Player name
		SKIP(scx, len);
		//System.out.println("Player "+plname);
		//Camera positions - 2 floats
		SKIP(scx, 8);
		//Unknown shorts - 2
		SKIP(scx, 4);
		//bool alliedvictory - 1 byte
		SKIP(scx, 1);
		//short countdiplomacy
		short countdiplomacy;
		READ(&countdiplomacy, sizeof(short), 1, scx);
		//char[countdiplomacy]
		SKIP(scx, countdiplomacy);
		//long[countdiplomacy]
		SKIP(scx, countdiplomacy*4);
		//long color
		SKIP(scx, 4);
		//float n_pldata
		float n_pldata;
		READ(&n_pldata, sizeof(float), 1, scx);
		//long nulls[n_pldata]
		SKIP(scx, 4*(int)n_pldata);
		//char nulls2[9]
		SKIP(scx, 9);
		//long end = -1
		SKIP(scx, 4);
	}

	//constant double 1.6
	SKIP(scx, 8);

	//start of triggers: 1st byte skipped
	SKIP(scx, 1);

	fclose(scx);

	return bytes_read;	
}

int Scenario::skiptoscenarioend(const char *filepath)
{
	FILE *scx = fopen(filepath, "rb");
	
	//we assume trigger_end is already set	
	//skip to trigger end
	long bytes_read=0;
	SKIP(scx, trigger_end);


	//read scn data
	long unknown3;
	long unknown4;
	READ(&unknown3, sizeof(long), 1, scx);
	READ(&unknown4, sizeof(long), 1, scx);

	if (unknown4==1)
	{
		SKIP(scx, 396); //hack
	}
	if (unknown3==1)
	{
		long filecount;
		READ(&filecount, sizeof(long), 1, scx);
		for (int i=0; i<filecount; i++)
		{
			long namelen;
			READ(&namelen, sizeof(long), 1, scx);
			SKIP(scx, namelen);
			long datalen;
			READ(&datalen, sizeof(long), 1, scx);
			SKIP(scx, datalen);
		}
	}

	fclose(scx);
	
	return bytes_read;
}


