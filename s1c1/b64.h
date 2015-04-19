/*
0 A            17 R            34 i            51 z
1 B            18 S            35 j            52 0
2 C            19 T            36 k            53 1
3 D            20 U            37 l            54 2
4 E            21 V            38 m            55 3
5 F            22 W            39 n            56 4
6 G            23 X            40 o            57 5
7 H            24 Y            41 p            58 6
8 I            25 Z            42 q            59 7
9 J            26 a            43 r            60 8
10 K            27 b            44 s            61 9
11 L            28 c            45 t            62 +
12 M            29 d            46 u            63 /
13 N            30 e            47 v
14 O            31 f            48 w         (pad) =
15 P            32 g            49 x
16 Q            33 h            50 y
*/

struct b64alpha
{
	int value;
	char encoding;

};

struct b64chunk
{
	unsigned int f1:1;
	unsigned int f2:1;
	unsigned int f3:1;
	unsigned int f4:1;
	unsigned int f5:1;
	unsigned int f6:1;
	unsigned int f7:1;
	unsigned int f8:1;
	unsigned int f9:1;
	unsigned int f10:1;
	unsigned int f11:1;
	unsigned int f12:1;
	unsigned int f13:1;
	unsigned int f14:1;
	unsigned int f15:1;
	unsigned int f16:1;
	unsigned int f17:1;
	unsigned int f18:1;
	unsigned int f19:1;
	unsigned int f20:1;
	unsigned int f21:1;
	unsigned int f22:1;
	unsigned int f23:1;
	unsigned int f24:1;
};

char *b64dict[64] = 
{"0,A","1,B","2,C","3,D","4,E","5,F","6,G","7,H",
"8,I","9,J","10,K","11,L","12,M","13,N","14,O",
"15,P","16,Q","17,R","18,S","19,T","20,U","21,V",
"22,W","23,X","24,Y","25,Z","26,a","27,b","28,c",
"29,d","30,e","31,f","32,g","33,h","34,i","35,j",
"36,k","37,l","38,m","39,n","40,o","41,p","42,q",
"43,r","44,s","45,t","46,u","47,v","48,w","49,x",
"50,y","51,z","52,0","53,1","54,2","55,3","56,4",
"57,5","58,6","59,7","60,8","61,9","62,+","63,/"};
