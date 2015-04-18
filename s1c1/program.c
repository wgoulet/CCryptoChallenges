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

const size_t MAXINT=65536;
char* trim(char* instr,char tflag,int num);
int checkvalidfile(const char* fname, int maxlen);

struct fdata {
        char fpath[65536];
        CIRCLEQ_ENTRY(fdata) entries;
};

struct conversions {
        size_t b64size;
        size_t binsize;
        char* b64data;
        char* bindata;
};

void main(int argc,char argv[])
{

