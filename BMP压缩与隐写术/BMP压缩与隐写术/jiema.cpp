#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BMP压缩与隐写术Dlg.h"
#include "BMP压缩与隐写术.h"
#define LENGTH_NAME_BMP 50
typedef long LONG;



int initBMPRead()//初始化BYTERGB
{
	int i;
	pBitMap b;

	bmpdata = new BYTE[sizeof(BYTE) * 5000];
	for (i = 0; i < b.bmlength; i++)
	{
		bmpBlu[i] = bmpdata[0 + 4 * i];
		bmpGre[i] = bmpdata[1 + 4 * i];
		bmpRed[i] = bmpdata[2 + 4 * i];
		bmpAlp[i] = bmpdata[3 + 4 * i];
		bmpCom[i] = bmpRed[i] + bmpGre[i] + bmpBlu[i] + i;
	}
	return 1;

}

int main()
{
	int i;
	int j = 0;
	char str1[100];
	pBitMap b;

	bmpRed = (int *)malloc(sizeof(int) * b.bmlength);
	bmpBlu = (int *)malloc(sizeof(int) * b.bmlength);
	bmpGre = (int *)malloc(sizeof(int) * b.bmlength);
	bmpAlp = (int *)malloc(sizeof(int) * b.bmlength);
	bmpCom = (int *)malloc(sizeof(int) * b.bmlength);

	int *p;
	unsigned long long int h = 0;
	for (i = 0; i < b.bmlength; i++)
	{
		for (p = &bmpCom[i]; *p; p++)
		{
			h = h * 31 + *p;
			if ((h % 5) == 0)
			{
				++j;
				str1[j] = bmpAlp[i];
				bmpAlp[i] = 0;
				if (str1[j] == '\0')
					break;
			}
		}
	}
	printf("隐写的数据是：", str1);
	system("pause");
}