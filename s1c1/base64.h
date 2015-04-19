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


int b64encode(char* indata,size_t inlen,char* outdata,size_t outlen);
