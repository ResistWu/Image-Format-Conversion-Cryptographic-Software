//
//  main.c
//  Hoffman
//
//  Created by leo on 16-6-7.
//  Copyright (c) 2016\u5e74 leo. All rights reserved.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "huff.h"
# define A 0x80000000
# define B 0x00000000
#include "BMP压缩与隐写术Dlg.h"
#include "BMP压缩与隐写术.h"


Huff::Huff()
{
	;
};



void Huff::swap(PTreeNode * x,PTreeNode * y){
    PTreeNode t = *x;
    *x = *y;
    *y = t;
}

//\u5feb\u901f\u6392\u5e8f
void Huff::QuickSort(PTreeNode * list, int start, int end){
    if (start >= end)
        return;
    int mid = list[end] -> frequency;
    int left = start, right = end - 1;
    while (left < right) {
        while (list[left]  -> frequency < mid && left < right)
            left++;
        while (list[right] -> frequency >= mid && left < right)
            right--;
        swap(&list[left], &list[right]);
    }
    if (list[left] -> frequency >= list[end] ->frequency)
        swap(&list[left], &list[end]);
    else
        left++;
    QuickSort(list, start, left - 1);
    QuickSort(list, left + 1, end);
}

//\u5efa\u7acb\u970d\u592b\u66fc\u6811
PTreeNode Huff::CreatHuffmanTree(PTreeNode * list, int length){
    PTreeNode node = (PTreeNode) malloc(sizeof(TreeNode));
    node -> frequency = list[0] -> frequency + list[1] -> frequency;
    node -> lchild = list[0];
    node -> rchild = list[1];
    node -> color = 0;
    list[1] = node;
    if(length == 2){
        return node;
    }
    else {
        list   ++;
        length --;
        QuickSort(list, 0, length - 1);//?
        return CreatHuffmanTree(list, length);
    }
}

//\u5efa\u7acb\u7801\u8868
void Huff::CreateCodeList(PTreeNode Node, PCodeListUnit codelist, char * stack, unsigned int pointer){
    if (Node -> lchild && Node -> rchild){//\u6839\u8282\u70b9\u6216\u4e2d\u95f4\u8282\u70b9
        //\u5de6\u5b50\u6811
        stack[pointer] = 0;
        pointer++;
        CreateCodeList(Node -> lchild, codelist, stack, pointer);
        pointer--;
        //\u53f3\u5b50\u6811
        stack[pointer] = 1;
        pointer++;
        CreateCodeList(Node -> rchild, codelist, stack, pointer);
        
    }
    else if(Node -> lchild == NULL && Node -> rchild == NULL ){//\u53f6\u5b50\u8282\u70b9
        int t = (int)Node -> color;
        for (unsigned int i = 0; i < pointer; i++) {
            codelist[t].code[i] = stack[i];
        }
        codelist[Node -> color].top = pointer - 1;//?????????????????????????
        return;
    }
}

unsigned int * Huff::HuffmanCode(unsigned char * pic, int length){//\u8bfb\u5165\u4ee5\u5b57\u8282\u7801\u5f62\u5f0f\u4fdd\u5b58\u7684\u4e00\u6bb5\u56fe\u5f62\u6587\u4ef6\uff0c\u4ee5\u53ca\u56fe\u5f62\u6587\u4ef6\u7684\u957f\u5ea6

	PTreeNode list[256];
	unsigned int l = 0;//编码后的长度
	char stack[256] = { 0 };
	int freq[256] = { 0 };
	int pointer_word = 0;//下标
	int pointer_bit = 0;//int内的位置
	for (int i = 0; i < 256; i++){
		list[i] = (PTreeNode)malloc(sizeof(TreeNode));
		list[i]->color = i;
		list[i]->lchild = NULL;
		list[i]->rchild = NULL;
		list[i]->frequency = 0;
	}
	for (int i = 0; i < length; i++){//统计频率
		list[pic[i]]->frequency++;
	}
	for (int i = 0; i < 256; i++){
		freq[i] = list[i]->frequency;
	}
	QuickSort(list, 0, 255);//按频率排序
	PTreeNode root = CreatHuffmanTree(list, 256);//建立霍夫曼
	//颜色为码表下标
	CreateCodeList(root, code_list, stack, 0);//编写码表
	for (int i = 0; i <= 255; i++){//计算长度(比特)
		l = l + (code_list[i].top + 1)*freq[i];
	}
	ll = (l + 31) / 32;
	y = l - (ll - 1) * 32;
	unsigned int * code_string = (unsigned int *)malloc(ll * sizeof(unsigned int));//以整数数组的方式保存编码后的结果，用尾部的元素放码表的指针

	for (unsigned int i = 0; i < ll; i++){//初始化
		code_string[i] = 0;
	}

	for (int i = 0; i < length; i++){//对于每一个色彩信息
		for (int j = 0; j <= code_list[pic[i]].top; j++){//对于译出的码字从0~top的每一位
			code_string[pointer_word] = code_string[pointer_word] << 1;//先右移
			code_string[pointer_word] += (int)code_list[pic[i]].code[j];//再加上码字
			pointer_bit++;
			if (pointer_bit == 32){
				pointer_word++;
				pointer_bit = 0;
			}
		}
		//pointer_bit = 0;
		//pointer_word = 0;
	}
	//code_string[ll] = (unsigned int)code_list;
	//printf("%lu",sizeof(code_list));
	return code_string;


}

char Huff::FindCode(int * stack, int top){//\u5bfb\u627e\u67d0\u4e00\u4e2a\u7801\u5b57\u7684\u6e90
    int flag = 1;
    char t = 0;
    for(int i = 0;i < 256; i++){
        flag = 1;
        if(top == code_list[i].top){
            for (int j = 0; j <= top; j ++) {
                if (stack[j] == code_list[i].code[j]) {
                    
                }
                else {
                    flag = 0;
                }
            }
        }
        else flag = 0;
        if (flag == 1){
            t = (char)i;
            break;
        };
        //flag = 1;
    }
    return t;
}

int Huff::CompareCode(int * stack, int top){
    int flag = 1;
    for(int i = 0; i < 256; i++){
        flag = 1;
        if(top == code_list[i].top){
            for (int j = 0; j <= top; j ++) {
                //int tt1 = stack[j];
                //int tt2 = code_list[i].code[j];
                if (stack[j] == code_list[i].code[j]) {
                    continue;
                }
                else {
                    flag = 0;
                }
            }
        }
        else flag = 0;
        i = i;
        if (flag == 1){
            break;
        };
        
    }
    return flag;
}

unsigned char * Huff::HuffmanDecode(unsigned int * code_string, int length){//length是编码的下标长度
	int stack[256] = { 0 };
	int stack_pointer = 0, counter = 0;
	unsigned int l = 0;
	//int p = 1;
	unsigned int a = 0;

	//-------------1------------------遍历确定解码长度
	for (int i = 0; i < length - 1; i++) {//开始
		unsigned int b = code_string[i];
		//printf("--%x--\n",b);
		for (int j = 0; j < 32; j++){
			a = b & A;
			if (a == A){
				stack[stack_pointer] = 1;
			}
			else if (a == B){
				stack[stack_pointer] = 0;
			}

			if (CompareCode(stack, stack_pointer)){
				l++;
				stack_pointer = 0;
				b = b << 1;

				continue;
			}
			stack_pointer++;
			b = b << 1;
			//i++;
		}

	}
	unsigned int c = code_string[length - 1];//最后的一个int会有空，需要特殊处理
	c = c << (32 - y);
	for (unsigned int j = 0; j < y; j++) {
		a = c & A;
		if (a == A){
			stack[stack_pointer] = 1;
		}
		else if (a == B){
			stack[stack_pointer] = 0;
		}
		if (CompareCode(stack, stack_pointer)){
			l++;
			stack_pointer = 0;
			//stack[0] = 0;
			c = c << 1;
			continue;
		}
		stack_pointer++;
		c = c << 1;
	}
	//------------------2---------------------解码
	stack_pointer = 0;
	counter = 0;
	unsigned char * wdstr = (unsigned char *)malloc(l * sizeof(unsigned char));

	for (int i = 0; i < length - 1; i++) {//开始解码
		for (int j = 0; j < 32; j++){
			a = code_string[i] & A;
			if (a == A){
				stack[stack_pointer] = 1;
			}
			else if (a == B){
				stack[stack_pointer] = 0;
			}

			if (CompareCode(stack, stack_pointer)){
				wdstr[counter] = FindCode(stack, stack_pointer);
				counter++;
				stack_pointer = 0;
				code_string[i] = code_string[i] << 1;
				//stack_pointer++;
				continue;
			}
			stack_pointer++;
			code_string[i] = code_string[i] << 1;
		}
	}
	wdstr[1] = wdstr[1];
	counter = counter;
	for (unsigned int i = 0; i < 32 - y; i++) {
		code_string[length - 1] *= 2;
	}
	//code_string[length - 1] *= 2;
	//word_string[1] = word_string[1];
	wdstr[1] = wdstr[1];

	for (unsigned int j = 0; j < y; j++) {////最后的一个int会有空，需要特殊处理
		a = code_string[length - 1] & A;
		if (a == A){
			stack[stack_pointer] = 1;
		}
		else if (a == B){
			stack[stack_pointer] = 0;
		}

		if (CompareCode(stack, stack_pointer)){
			wdstr[counter] = FindCode(stack, stack_pointer);
			counter++;
			stack_pointer = 0;
			code_string[length - 1] = code_string[length - 1] << 1;
			continue;
		}
		stack_pointer++;
		code_string[length - 1] = code_string[length - 1] << 1;
	}
	lll = l;
	return wdstr;
}

//\u7f16\u7801\uff0c
//\u8f93\u5165\u4e00\u4e2a\u5b57\u7b26\u6570\u7ec4\uff0c
//\u8f93\u51fa\u4e00\u4e2a\u6574\u6570\u6570\u7ec4\uff1b
//\u89e3\u7801\u53cd\u4e4b\u3002
/*
int main(int argc, const char * argv[]) {
    char a[43] = {'a','a','a','a','a','a','a','a','a','a','a','a','b','b','b','b','b','b','c','c','a','a','a','a','a','a','a','a','a','a','a','a','b','b','b','b','b','b','c','c','d','d','d'};
    printf("Huffman coding...\\n");
    unsigned int * t1 =HuffmanCode(a, 43);
    for (int i = 0 ; i < ll; i++){
        printf("0x%x\\n", t1[i]);
    }
    printf("Huffman decoding...\\n");
    char * t2 = HuffmanDecode(t1, ll);
    for (int i = 0 ; i < lll; i++){
        printf("%c", t2[i]);
    }
    
    return 0;
    
}*/
