
// BMPѹ������д��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//



#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
//#include "huff.h"

#ifndef CLASSNAME_huff
#define CLASSNAME_huff
typedef struct CodeListUnit{//���Ԫ
	int top;//�������±�
	int code[256];//0 or 1
}CodeListUnit, *PCodeListUnit;
#endif
// CBMPѹ������д��App: 
// �йش����ʵ�֣������ BMPѹ������д��.cpp
//

class CBMPѹ������д��App : public CWinApp
{
public:
	CBMPѹ������д��App();
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

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBMPѹ������д��App app;