#include <iostream>
#include "main.h"
extern "C" {
	void _log(int i);
	//#include "cHeader.h"
}
using namespace std;



char str[] = { "abcdefg" };
extern int a;
extern int b;
int maxbb(int l,int r) {
	return l > r ? l : r;
}

extern int _a;
extern int _b;
int maxAB(int a,int b);
int main2() {
	/*cout << "a:" << _a << " b:" << _b << endl;
	cout << maxAB(100,200) << endl;*/
	_log(100);
	return 1;
}
int a = 10;
int b = 20;



