#include <cstdio>
#include <cstdlib>
# define A 0x80000000
# define B 0x00000000

typedef struct TreeNode{
	unsigned char color;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
	int frequency;
}TreeNode, *PTreeNode;

#ifndef CLASSNAME_huff
#define CLASSNAME_huff
typedef struct CodeListUnit{//码表单元
	int top;//顶部的下标
	int code[256];//0 or 1
}CodeListUnit, *PCodeListUnit;
#endif

class Huff{
public:
	Huff();
	void swap(PTreeNode*, PTreeNode*);
	void QuickSort(PTreeNode*, int, int);
	PTreeNode CreatHuffmanTree(PTreeNode* , int );
	void CreateCodeList(PTreeNode , PCodeListUnit , char* , unsigned int );
	unsigned int * HuffmanCode(unsigned char *, int );
	char FindCode(int * , int );
	int CompareCode(int * , int );
	unsigned char * HuffmanDecode(unsigned int * , int );


	CodeListUnit *code_list= (PCodeListUnit)malloc(sizeof(CodeListUnit) * 256);//颜色为码表下标
	unsigned int ll=0;
	unsigned int lll=0;
	unsigned int y=0;//余数

};
