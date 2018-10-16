#ifndef CLASSNAME_run
#define CLASSNAME_run

//#include "stdafx.h"
#include "iostream"

using namespace std;
struct Run_list{
	BYTE pos;
	struct Run_list *next;
};
struct Run_pre_list{
	int pos;
	struct Run_pre_list *next;
};
typedef struct Run_list run_list;
typedef struct Run_pre_list run_pre_list;
class Run
{
public:
	Run(BITMAP);
	Run(int,int,int);
	run_list* create(void);
	run_pre_list* pre_create(void);
	void add(run_list*, int);
	void del(run_list*);
	int length(run_list*);
	int length(run_pre_list*);
	void printlist(run_list*);
	void printlist(run_pre_list*);//��������
	void make();
	void demake();
	void compression();
	void decompression();
	string filehead;//�ļ�ͷ
	int bmpx, bmpy, bmpxb, bmpsize;//����
	int bmpxy;
	int prelength;//�γ̱���������
	run_pre_list *prelist;//�γ̱�������
	run_list *pr;
	run_list *pg;
	run_list *pb;
	run_list *result;
};
#endif