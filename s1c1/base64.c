#include "base64.h"

size_t MAXSTR=65536;
char* b64dict[64] =
{"0,A","1,B","2,C","3,D","4,E","5,F","6,G","7,H",
"8,I","9,J","10,K","11,L","12,M","13,N","14,O",
"15,P","16,Q","17,R","18,S","19,T","20,U","21,V",
"22,W","23,X","24,Y","25,Z","26,a","27,b","28,c",
"29,d","30,e","31,f","32,g","33,h","34,i","35,j",
"36,k","37,l","38,m","39,n","40,o","41,p","42,q",
"43,r","44,s","45,t","46,u","47,v","48,w","49,x",
"50,y","51,z","52,0","53,1","54,2","55,3","56,4",
"57,5","58,6","59,7","60,8","61,9","62,+","63,/"};

int b64encode(char* indata,size_t inlen,char* outdata,size_t outlen)
{
	size_t alphalen = 64;
	char* disp = malloc(MAXSTR);
	struct b64alpha b64lookup[64];
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
		}
		
        }

	FILE* fp = fmemopen(indata,inlen,"r");
	FILE* fout = fmemopen(outdata,outlen,"w");
 
	int charct = 0;
	for(;;)
	{
		if(feof(fp))
		{
			break;
		}
		// struct b64chunk is a packed structure
		// with 24 bit fields. Makes it easy to manipulate
		// individual bits.

		struct b64chunk* chunk = malloc(sizeof(struct b64chunk));
		bzero(chunk,sizeof(struct b64chunk));
		int numb = fread(chunk,1,3,fp);
		int char1 = 0;
		int char2 = 0;
		int char3 = 0;
		int char4 = 0;
		// if at end of input stream and no bytes
		// left; exit
		if(numb == 0)
		{
			break;
		}

		// if we have less than a full chunk of
		// data remaining, perform padding.
                if((numb < 3) && (numb > 0))
                {
			switch(numb)
			{
				case 1:
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
					putc(b64lookup[char1].encoding,fout);
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
					putc(b64lookup[char2].encoding,fout);
					putc('=',fout);
					putc('=',fout);
					break;
				case 2:
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
                                        putc(b64lookup[char1].encoding,fout);
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
                                        putc(b64lookup[char2].encoding,fout);
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
					putc(b64lookup[char3].encoding,fout);
					putc('=',fout);
					break;
			}

			break;
		}
		// construct 6 bit values by adding
		// each field value to an int, shifting left
		// after each add

               	// swap order of LSB when reading data from file 
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
		putc(b64lookup[char1].encoding,fout);
		charct++;

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
		putc(b64lookup[char2].encoding,fout);
		charct++;

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
		putc(b64lookup[char3].encoding,fout);
		charct++;

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
		putc(b64lookup[char4].encoding,fout);
		charct++;
		// linewrap output at 76 chars
		// to match gnu base64
		if(charct % 76 == 0)
		{
			putc('\n',fout);
		}
		free(chunk);
	}
	free(disp);
	fclose(fp);
	fclose(fout);
	return charct;
}
