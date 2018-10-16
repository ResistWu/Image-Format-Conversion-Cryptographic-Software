#ifndef CLASSNAME_sec
#define CLASSNAME_sec
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef unsigned char BYTE;
#define LENGTH_NAME_BMP 50
typedef long LONG;

typedef struct pBitMap
{
	LONG bmWidth;
	LONG bmHeight;
	LONG bmlength = bmWidth*bmHeight;
}BitMap;

class Secret{
public:
	Secret(int,int);
	void yinxie( CString);
	CString jiema();
	//int initBMPRead();
	int x, y;
	CString msg;
	BYTE *bmpdata;
	BYTE *bmpRed;
	BYTE *bmpGre;
	BYTE *bmpBlu;
	BYTE *bmpAlp;
	BYTE *bmpCom;
};
#endif