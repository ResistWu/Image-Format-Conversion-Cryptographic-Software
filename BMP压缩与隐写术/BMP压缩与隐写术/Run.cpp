#pragma once
#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "Run.h"
#include "time.h"
#include "math.h"
#include "BMP压缩与隐写术Dlg.h"
#include "BMP压缩与隐写术.h"


using namespace std;

Run::Run(BITMAP pBitMap)
	{
		bmpx = (int)pBitMap.bmWidth;
		bmpxb = (int)pBitMap.bmWidthBytes;
		bmpy = (int)pBitMap.bmHeight;
		bmpxy = bmpx*bmpy;//加点东西！
		bmpsize = bmpxb*bmpy;
		prelist = pre_create();
		pr = create();
		pg = create();
		pb = create();
		result = create();
		make();

	};

Run::Run(int x,int y,int len)
{
	CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();
	bmpx = x;
	bmpy = y;
	bmpxb = x*4;
	app->runlength = len;
	bmpxy = bmpx*bmpy;
	bmpsize = x*y*4;
	prelist = pre_create();
	pr = create();
	pg = create();
	pb = create();
	result = create();
	demake();

};

	run_list* Run::create(void)
	{
		run_list *head;
		head = (run_list*)malloc(sizeof(run_list));
		head->pos = 0;
		head->next = NULL;
		return head;
	}

	run_pre_list* Run::pre_create(void)
	{
		run_pre_list *head;
		head = (run_pre_list*)malloc(sizeof(run_pre_list));
		head->pos = 0;
		head->next = NULL;
		return head;
	}

	void Run::add(run_list* l, int a)
	{
		run_list *temp = l;
		run_list *p = (run_list*)malloc(sizeof(run_list));
		p->pos = a;
		p->next = NULL;
		while (temp->next){
			temp = temp->next;
		}
		temp->next = p;
	}

	int Run::length(run_list* l)
	{
		run_list *temp;
		temp = l;
		int i;
		for (i = 1; temp->next != NULL; i++){
			temp = temp->next;
		}
		return i;
	}

	int Run::length(run_pre_list* l)
	{
		run_pre_list *temp;
		temp = l;
		int i;
		for (i = 1; temp->next != NULL; i++){
			temp = temp->next;
		}
		return i;
	}

	void Run::make()
	{
		run_list *tempr = pr, *tempg = pg, *tempb = pb;
		CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();
		for (int i = 0; i < bmpxy; i++){
			run_list *ppr = (run_list*)malloc(sizeof(run_list));
			run_list *ppg = (run_list*)malloc(sizeof(run_list));
			run_list *ppb = (run_list*)malloc(sizeof(run_list));
			ppr->pos = app->bmpdata[0 + 4 * i];
			ppg->pos = app->bmpdata[1 + 4 * i];
			ppb->pos = app->bmpdata[2 + 4 * i];
			tempr->next = ppr;
			tempg->next = ppg;
			tempb->next = ppb;
			tempr = tempr->next;
			tempg = tempg->next;
			tempb = tempb->next;
		}
		tempr->next = NULL;
		tempg->next = NULL;
		tempb->next = NULL;

	}

	void Run::demake()
	{
		CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();
		run_pre_list *tempp = prelist;
		run_list *temp = result;//result要换成哈夫曼结果！！！
		for (int i = 0; i < app->runheadlength; i++){
			
			run_pre_list *p = (run_pre_list*)malloc(sizeof(run_pre_list));
			p->pos = app->runhead[i];
			p->next = NULL;
			tempp->next = p;
			tempp = tempp->next;
		}
		for (int i = 0; i < app->runlength; i++){
			run_list *p = (run_list*)malloc(sizeof(run_list));
			p->pos = app->rundata[i];
			p->next = NULL;
			temp->next = p;
			temp = temp->next;
		}
	}

	void Run::printlist(run_list* l)
	{	
		CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();
		run_list *temp = l->next;
		int a; CString s;
		//CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();
		//CFile file(_T("data.txt"), CFile::modeWrite);
		//file.SeekToEnd();
		int i = 0;
		//for (temp=result->next; temp->next != NULL; temp = temp->next){
		//	count++;
		//}
		//app->rundata = new BYTE[count];
		for (; temp != NULL; temp = temp->next){

			a = (int)temp->pos;
			s.Format(_T("%d~"), a);
			//MessageBox(NULL,s,NULL,NULL);
			//file.Write(s, 2*s.GetLength());
			
			app->rundata[i] = temp->pos;
			i++;
		}
		//file.Close();
		
	}

	void Run::printlist(run_pre_list* l)
	{
		CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();
		run_pre_list *temp;
		temp = l->next;
		int i = 0;
		int a; CString s;
		//CFile file(_T("data.txt"), CFile::modeWrite | CFile::modeCreate);
		for (; temp != NULL; temp = temp->next){
			a = temp->pos;
			s.Format(_T("%d~"), a);
			//MessageBox(NULL,s,NULL,NULL);
			//file.Write(s, 2*s.GetLength());
			app->runhead[i] = temp->pos;//youyong
			i++;
		}
		//file.Write(_T("--"),4 );
		app->runheadlength = i;
		//file.Close();
	}

	void Run::compression()
	{
		int count = 1;
		BYTE time = 0;
		run_list *temp,*ttemp;
		run_pre_list *ptemp=prelist;
		result = pr;
		temp = pr;
		while (temp->next != NULL){
			temp = temp->next;
		}
		temp->next = pg->next;
		while (temp->next != NULL){
			temp = temp->next;
		}
		temp->next = pb->next;
		cout << endl;
		
		temp = result->next;


		CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();
		int a; CString s;
		


		ttemp = temp;
		for (; temp!= NULL;temp=temp->next){
			if ((temp->next != NULL)&&(temp->pos == temp->next->pos)&&(time < 254)){
				time++;
				if (time == 1)
					ttemp = temp;
			}
			else{
				count++;
				if (time >= 3){
					for (BYTE i = 0; i < time-1; i++){
						temp = ttemp->next;
						ttemp->next = ttemp->next->next;
						free(temp);
					}
					temp = ttemp->next;
					temp->pos = time + 1;
					//在prelist链表中追加
					run_pre_list *pp;
					pp = (run_pre_list*)malloc(sizeof(run_pre_list));
					pp->pos = count - 1;
					pp->next = NULL;
					ptemp->next = pp;
					ptemp = ptemp->next;
					//add(prelist, count-1);
					count++;
				}
				time = 0;
			}
		}
		cout << "压缩结果为：";
		temp = result;
		//int a; CString s;
		
		//CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();
		app->runlength = length(result);
		app->runhead = (int*)malloc(sizeof(int)*length(prelist));
		app->rundata = new BYTE[app->runlength];
		printlist(prelist);
		printlist(result);
		a = length(prelist);
		s.Format(_T("-%d "), a);
		MessageBox(NULL, s, NULL, NULL);
		cout << endl << "###" << count << "###" << endl;
		/*有bug！！！
		for (; pr->next != NULL;){
			temp = pr;
			pr = pr->next;
			free(temp);
			temp = pg;
			pg = pg->next;
			free(temp);
			temp = pb;
			pb = pb->next;
			free(temp);
		}*/
	}

	void Run::decompression()
	{
		CBMP压缩与隐写术App *app = (CBMP压缩与隐写术App*)AfxGetApp();
		int count =0;
		int pre = 0;
		BYTE time = 0;
		BYTE pos = 0;
		int j = 0;
		int prelen = app->runheadlength; 
		int a,b; CString s,ss;
		run_list *temp;
		temp = result;
		int asd = 0;
		//CFile f1ile(_T("data1.txt"), CFile::modeWrite | CFile::modeCreate);
		
		temp = result;



		for (int i = 0; i < app->runlength; i++){
			if (count == app->runhead[pre]){

				
				//44444444444444444444444444444444
				time = temp->next->pos;
				pos = temp->pos;
				temp->next->pos = pos;
				temp = temp->next;
				/*
				a = pos; b = time;
				s.Format(_T("%d-%d "), a, b);
				MessageBox(NULL, s, NULL, NULL);
				*/
				for (BYTE i = 0; i < time - 2; i++){
					run_list *p = (run_list*)malloc(sizeof(run_list));
					p->pos = pos;
					p->next = temp->next;
					temp->next = p;
					temp = temp->next;
					
					asd++;
				}
				asd = 0;
				pre++;
				//count++;
			}
			else{
				temp = temp->next;
			}
			count++;
			if (pre == prelen)
				break;
		}

		
		temp = result->next; int lll=length(temp);
		/*
		int k = 0;
		for (int i = 0; i < 100; i++){
			
			a = temp->pos; b = app->bmpdata[k];
			temp = temp->next;
			k++; if (k % 4 == 3)k++;
			s.Format(_T("%d-%d"), a, b);
			MessageBox(NULL,s,NULL,NULL);
		}
		*/
		temp = result->next;
		app->bmpdata2 = new BYTE[bmpsize];
		for (int i = 0; i < bmpsize; i++) app->bmpdata2[i] = 0;//初始化
		
		for (int i = 0; i < bmpy; i++){
			for (int j = 0; j < bmpx; j++){
				app->bmpdata2[i*bmpxb + j * 4] = temp->pos;
				temp = temp->next;

			}
		}
		
		for (int i = 0; i < bmpy; i++){
			for (int j = 0; j < bmpx; j++){
				app->bmpdata2[i*bmpxb + j*4+1] = temp->pos;
				temp = temp->next;
			}
		}
		for (int i = 0; i < bmpy; i++){
			for (int j = 0; j < bmpx; j++){
				app->bmpdata2[i*bmpxb + j*4+2] = temp->pos;

				temp = temp->next;
			}
		}
		int ll = length(temp);
		/*
		for (int i = 0; i < bmpsize; i++){
			a = app->bmpdata[i];
			s.Format(_T("-%d "), a);
			MessageBox(NULL, s, NULL, NULL);
		}
		//int a; CString s;
		
		for (int i = 0; i < 20; i++){
			a = app->bmpdata[i];
			s.Format(_T("-%d "), a);
			MessageBox(NULL, s, NULL, NULL);
		}
		
		*/

	}