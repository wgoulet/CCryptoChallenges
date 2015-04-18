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

const size_t MAXINT=65536;

void main(int argc,char argv[])
{
	size_t alphalen = 65;
	char* disp = malloc(MAXINT);
	for(int i = 0; i < alphalen; i++)
        {
	        char* e = b64dict[i];
		snprintf(disp,255,"%s",e);
		puts(disp);
		
        }

}
