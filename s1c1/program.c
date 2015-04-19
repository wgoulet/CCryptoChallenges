#include "base64.h"

void main(int argc,char* argv[])
{

	FILE* fp = fopen(argv[1],"r");
	struct stat* finfo = malloc(sizeof(struct stat));
	int numb = 0;
	if(lstat(argv[1],finfo) != 0)
	{
		return;
	}
	numb = finfo->st_size;
	char* buf = malloc(numb);
	fread(buf,1,numb,fp);
	fclose(fp);
	char* buf2 = malloc(numb * 2);
	int b64ct = b64encode(buf,numb,buf2,numb * 2);
	if(b64ct > 0)
	{
		puts(buf2);
	}
	free(finfo);
	free(buf);
	free(buf2);
}
