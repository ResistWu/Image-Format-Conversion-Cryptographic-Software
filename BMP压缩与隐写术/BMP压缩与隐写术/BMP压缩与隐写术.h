
// BMP压缩与隐写术.h : PROJECT_NAME 应用程序的主头文件
//



#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
//#include "huff.h"

#ifndef CLASSNAME_huff
#define CLASSNAME_huff
typedef struct CodeListUnit{//码表单元
	int top;//顶部的下标
	int code[256];//0 or 1
}CodeListUnit, *PCodeListUnit;
#endif
// CBMP压缩与隐写术App: 
// 有关此类的实现，请参阅 BMP压缩与隐写术.cpp
//

class CBMP压缩与隐写术App : public CWinApp
{
public:
	CBMP压缩与隐写术App();
	BYTE *bmphead;
	BYTE *bmpdata;
	BYTE *rdata;
	BYTE *gdata;
	BYTE *bdata;
	BYTE *adata;
	BYTE *bmpdata2;
	BYTE *rundata;
	int runheadlength;
	int *runhead;
	int runlength;
	unsigned int *huffdata;
	CodeListUnit *codelist_r;
	CodeListUnit *codelist_g;
	CodeListUnit *codelist_b;
	//int rlength;
	//int glength;
	//int blength;
	unsigned char *md5code;
	BYTE flag;
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CBMP压缩与隐写术App app;