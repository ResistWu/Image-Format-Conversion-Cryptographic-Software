#include "iostream"
#include "fstream"
#include "Run.h"
using namespace std;

int main()
{
	string file = "abcdefghij||2||2||(13,13,13)(15,15,15)(17,17,17)(88,88,89)";
	Run bmp(file);
	//bmp.printlist(bmp.pr);
	//bmp.printlist(bmp.pg);
	//bmp.printlist(bmp.pb);
	bmp.compression();
	system("pause");
}