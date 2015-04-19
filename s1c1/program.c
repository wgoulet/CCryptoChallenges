#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <search.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <errno.h>
#include <netdb.h>
#include "b64.h"

const size_t MAXSTR=65536;

void main(int argc,char* argv[])
{
	size_t alphalen = 64;
	char* disp = malloc(MAXSTR);
	struct b64alpha b64lookup[64];
	if(argc != 2)
	{
		puts("No filename specified; exiting");
		return;
	}
	for(int i = 0; i < alphalen; i++)
        {
	        char* e = b64dict[i];
		char* enc = malloc(255);
		errno = 0;
		// strtol stops parsing number
		// at first non-numeric char
		// so enc will point to remaining
		// string
		int v = strtol(b64dict[i],&enc,10);
		if(errno == 0)
		{
			b64lookup[i].value = v;
			// skip past the comma in our  dictionary
			enc++;
			// store the char in the encoding
			b64lookup[i].encoding = *enc;
			//memcpy(&b64lookup[i].encoding,enc,strnlen(enc,MAXSTR));
			////free(enc);
		}
		
		//snprintf(disp,255,"%d -> %c",b64lookup[i].value,b64lookup[i].encoding);
        }

	FILE* fp = fopen(argv[1],"r");
	int charct = 0;
	for(;;)
	{
		if(feof(fp))
		{
			break;
		}
		struct b64chunk* chunk = malloc(sizeof(struct b64chunk));
		bzero(chunk,sizeof(struct b64chunk));
		int numb = fread(chunk,1,3,fp);
                if(numb < 3)
                {
			//snprintf(disp,255,"Bytes padding: %d",numb);
			for(int j = 0; j < numb; j++)
			{
				putchar('=');
				charct++;
			}
			break;
		}
		// construct 6 bit values by adding
		// each field value to an int, shifting left
		// after each add
                
		int char1 = 0;
		char1 += chunk->f8;
		char1 = char1 << 1;
		char1 += chunk->f7;
		char1 = char1 << 1;
		char1 += chunk->f6;
		char1 = char1 << 1;
		char1 += chunk->f5;
		char1 = char1 << 1;
		char1 += chunk->f4;
		char1 = char1 << 1;
		char1 += chunk->f3;
		snprintf(disp,255,"%d",b64lookup[char1].encoding);
		putchar(b64lookup[char1].encoding);
		charct++;

		int char2 = 0;
		char2 += chunk->f2;
		char2 = char2 << 1;
		char2 += chunk->f1;
		char2 = char2 << 1;
		char2 += chunk->f16;
		char2 = char2 << 1;
		char2 += chunk->f15;
		char2 = char2 << 1;
		char2 += chunk->f14;
		char2 = char2 << 1;
		char2 += chunk->f13;
		snprintf(disp,255,"%d",b64lookup[char2].encoding);
		putchar(b64lookup[char2].encoding);
		charct++;

		int char3 = 0;
		char3 += chunk->f12;
		char3 = char3 << 1;
		char3 += chunk->f11;
		char3 = char3 << 1;
		char3 += chunk->f10;
		char3 = char3 << 1;
		char3 += chunk->f9;
		char3 = char3 << 1;
		char3 += chunk->f24;
		char3 = char3 << 1;
		char3 += chunk->f23;
		snprintf(disp,255,"%d",b64lookup[char3].encoding);
		putchar(b64lookup[char3].encoding);
		charct++;

		int char4 = 0;
		char4 += chunk->f22;
		char4 = char4 << 1;
		char4 += chunk->f21;
		char4 = char4 << 1;
		char4 += chunk->f20;
		char4 = char4 << 1;
		char4 += chunk->f19;
		char4 = char4 << 1;
		char4 += chunk->f18;
		char4 = char4 << 1;
		char4 += chunk->f17;
		snprintf(disp,255,"%d",b64lookup[char4].encoding);
		putchar(b64lookup[char4].encoding);
		charct++;
		// linewrap output at 76 chars
		// to match gnu base64
		if(charct % 76 == 0)
		{
			puts("");
		}
		free(chunk);
	}	
	free(disp);
	puts("");
}
