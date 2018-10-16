#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secret.h"
#include "BMPÑ¹ËõÓëÒþÐ´ÊõDlg.h"
#include "BMPÑ¹ËõÓëÒþÐ´Êõ.h"


Secret::Secret(int x,int y)//³õÊ¼»¯BYTERGB
{
	CBMPÑ¹ËõÓëÒþÐ´ÊõApp *app = (CBMPÑ¹ËõÓëÒþÐ´ÊõApp*)AfxGetApp();
	this->x = x; this->y = y;
	int i;
	bmpRed = app->rdata;
	bmpGre = app->gdata;
	bmpBlu = app->bdata;
	bmpAlp = app->adata;
	bmpCom = (BYTE*)malloc(x*y);
	for (int i = 0; i < x*y; i++){
		bmpCom[i] = bmpRed[i] + bmpGre[i] + i;
	}
	
}

void Secret::yinxie(CString msg)
{
	int i;
	int j = 0;
	
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, msg, -1, NULL, NULL, 0, NULL);
	char *str = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, msg, -1, str, dwNum, 0, NULL);

	
	BYTE *p;
	unsigned long long int h = 0;
	for (i = 0; i < x*y; i++)
	{
		if (bmpCom[i] % 40 == 5){
			bmpBlu[i] = str[j];
			BYTE a = bmpBlu[i];
			if (str[j] == '\0'){
				break;
			}
			j++;


		}
		
	}
	
}

CString Secret::jiema()
{
	int i;
	int j = 0;
	BYTE *p;
	char str[100];
	unsigned long long int h = 0;
	for (i = 0; i < x*y; i++)
	{
		if (bmpCom[i] % 40 == 5){
			str[j] = bmpBlu[i];
			if (bmpBlu[i] == '\0'){
				break;
			}
			j++;
		}
	}
	CString msg;
	//LPTSTR pstr = _T("Char  test");
	msg.Format(_T("%s"), CStringW(str));
	return msg;

}