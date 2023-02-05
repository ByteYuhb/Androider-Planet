// 20221229-demo-cAndCpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <bitset>
#include "ExternTest.h"
#include "Base.h"
#include "Triangel.h"
#include "Rectangel.h"


using namespace std;

#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
//测试：字符和字符地址的转换问题
void charBug() 
{
	//char c1 = 'yes';//取最后一个字符:'s'
	//char c2 = "yes";//报错：const char*类型的值不能用于初始化char类型的实体
	//char c3 = &c1;//报错： char*类型的值不能用于初始化char类型的实体


	//char* cs1 = '/'; //报错：char 类型的值不能用于初始化const char*类型的实体
	//const char* cs2 = "/";//正确取值为：'/''\0'
	//const char* cs3 = &c1;//正确取到c1的地址值

	//c++
	string s1(1, 'yes');//s
	string s2(3, 'yes');//sss

	string s3("yes");//yes
	string s4("/");// /
	string s5(1,'/');// /

	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
}
//测试：数组作为参数传入的问题
double average(int arr[]) {
	double result = 0.0;
	int len = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < len; i++) {
		result += arr[i];
	}
	return result/len;
}
double average2(vector<int>& vec) {
	double result = 0.0;

	vector<int>::iterator it = vec.begin();
	for (; it != vec.end(); ++it) {
		result += *it;
	}
	return result / vec.size();
}
//测试二进制位移引起的补位问题 逻辑位移 or算术位移
void bitMove() {
	char c1 = 0x63;//0110 0011
	c1 = c1 << 4;//右移4位
	printf("0x%02x\n",c1); //推算：0011 0000 ->0x30

	c1 = 0x63;
	c1 = c1 >> 4;//左移4位
	printf("0x%02x\n", c1);//推算：0000 0110 ->0x06

	char c2 = 0x93;//1001 0011
	printf("%d\n", c2);
	c2 = c2 << 4;//右移4位
	printf("0x%02x\n", c2); //推算：0011 0000 ->0x30

	c2 = 0x93;
	c2 = c2 >> 4;//左移4位
	printf("0x%02x\n", c2);//推算：0000 0110 ->0x06?
}


void bitMove1() {
	unsigned char x = 0xFF;
	const unsigned char BACK_UP = (1 << 7);
	const unsigned char ADMIN = (1 << 8);
	//printf("0x%x\n", BACK_UP);
	//printf("0x%x\n", ADMIN);

	if (x & BACK_UP) {
		cout << "BACK_UP" << endl;
	}
	if (x & ADMIN) {
		cout << "ADMIN" << endl;
	}
}
void bitMove2() {
	bitset<10> x = 0xFF;
	const bitset<10> BACK_UP = (1 << 7);
	const bitset<10> ADMIN = (1 << 8);
	printf("BACK_UP:0x%x\n", BACK_UP);
	cout<<"BACK_UP:binary:" << BACK_UP << endl;
	printf("ADMIN:0x%x\n", ADMIN);
	cout << "ADMIN:binary:" << ADMIN << endl;

	if ((x & BACK_UP) == BACK_UP) {
		cout << "BACK_UP" << endl;
	}
	if ((x & ADMIN) == ADMIN) {
		cout << "ADMIN" << endl;
	}
}
//测试：强制转换问题
void cast1() {
	int arr[] = { 1,2,3,4 };
	cout <<"arr size:" << sizeof(arr) / sizeof(arr[0]) << endl;
	int thresholp = -1;
	int len = sizeof(arr) / sizeof(arr[0]);
	if (len > thresholp) {
		cout << "arr len is big than thresholp" << endl;
	}
	else
	{
		cout << "thresholp is big than arr len" << endl;
	}
	cout << (unsigned int)(-1) << endl;
}

//测试：隐式强制转换问题
void _cast1() {
	int arr[] = { 1,2,3,4 };
	cout << "arr size:" << sizeof(arr) / sizeof(arr[0]) << endl;
	int thresholp = -1;
	int len = sizeof(arr) / sizeof(arr[0]);
	if (len > thresholp) {
		cout << "arr len is big than thresholp" << endl;
	}
	else
	{
		cout << "thresholp is big than arr len" << endl;
	}
	cout << (unsigned int)(-1) << endl;
}

void cast2() {
	double result = 0.0;
	int arr[] = { 10,20,30,40 };
	unsigned int len  = sizeof(arr) / sizeof(arr[0]);
	for (unsigned int i = 0; i < len; i++) {
		result += (static_cast<double>(1))/ arr[i];
	}
	cout << result << endl;
	return;
}
//测试;整数溢出问题
void intOverflow1() {
	int i = 0x7ffffff0;
	for (; i > 0; i++) {
		cout << "adding" << endl;
	}
	cout << "end ??" <<i<< endl;
}

//
void intOverflow2() {
	cpp_int a = 200, b = 300, c = 400, d = 500;
	cout << a * b * c * d << endl;
}

void strTest() {
	char str1[] = "abcdef";
	cout << "str1_strlen:" << strlen(str1) << endl;
	cout <<"str1_sizeof:" << sizeof(str1) / sizeof(str1[0]) << endl;

	char str2[] = "abc\0def";
	cout << "str2_strlen:" << strlen(str2) << endl;
	cout << "str2_sizeof:" << sizeof(str2) / sizeof(str2[0]) << endl;
}
void strTest1() {
	string s1 = "123";
	const char *str = s1.c_str();
	str += 1;
	const char * const str1 = s1.c_str();

}
extern int cmax;
extern int cmax2;
//extern char str[];
//extern char *str;

void externTest() {
	/*cout << maxAB(a, b) << endl;
	cout << cmax2 << endl;
	cmax2 = 10;
	cout << cmax2 << endl;*/

	//cout << *str << endl;
}

extern int maxbb(int l, int r);
#pragma pack(1)
struct tree

{

	int height;

	int age;

	char tag;

};
#pragma pack
void pointTest() {
	//{
	//	int str[] = {1,2,3};
	//	int* pStr = str;
	//	int* x = pStr + 3;
	//	char a1 = 'a';
	//	//pStr = &a1;
	//	//*pStr = 1;

	//	*str = a1;
	//	*(pStr + 100) = a1;

	//	//char a[] = "helloworld";
	//	//const char* pCharA = a;
	//	//pCharA = &a1;
	//	//*pCharA = 1;

	//	//char _a[] = "helloworld";
	//	//char const * _pCharA = _a;
	//	//_pCharA = &a1;
	//	//*_pCharA = 1;

	//	//char b[] = "helloworld";
	//	//char* const pCharB = b;
	//	//pCharB = &a1;
	//	//*pCharB = 1;

	//	//char c[] = "helloworld";
	//	//const char* const pCharC = c;
	//	//pCharC = &a1;
	//	//*pCharC = 1;

	//	/*char a = 'a';
	//	char* pa = &a;
	//	char** ppa = &pa;*/

	//	int c[] = {1,2,3};;
	//	int* pChar = c;

	//	*pChar = 23;
	//	char c1 = *pChar;

	//	char c2 = *pChar + 1;
	//	//*pChar + 1 = 'b';//编译报错，*pChar + 1不是一个对象，只是一个常量，不能作为左值
	//	
	//	*(pChar + 1) = 34;
	//	char c3 = *(pChar + 1);
	//	cout << c3 << endl;

	//	int buffer[128] = { 0 };
	//	int* tmp_ptr = buffer;
	//	struct tree* t_ptr = (struct tree*)tmp_ptr;
	//	int* t_ptr_new = NULL;
	//	t_ptr_new = (int*)(t_ptr + 1);

	//	printf("t_ptr_new point to buffer[%ld]\n", t_ptr_new - tmp_ptr);

	//	//char buffer[128] = { 0 };
	//	//char* tmp_ptr = buffer;
	//	//struct tree* t_ptr = (struct tree*)tmp_ptr;
	//	//char* t_ptr_new = NULL;
	//	//t_ptr_new = (char*)(t_ptr + 1);

	//	//printf("t_ptr_new point to buffer[%ld]\n", t_ptr_new - tmp_ptr);

	//	char c4[] = "abcdefg"; //c4->0x0022f53c
	//	char* pc = c4;//pc指向c4 ->0x0022f53c

	//	char* pc1 = pc++;//pc1等于pc也就是c4 ->0x0022f53c，此后pc变为pc+1 也就是c4+1:  = 0x0022f53d
	//	char* pc2 = ++pc; //pc2等于pc+1=0x0022f53e 此后pc变为:c4+2: = 0x0022f53e

	//	char* pc3 = --pc;//pc3等于pc-1 = 0x0022f53d 此后 pc变为c4+1: = 0x0022f53d
	//	char* pc4 = pc--;//pc4等于pc = 0x0022f53d ，此后pc变为c4: = 0x0022f53c
	//	
	//	(++pc) = pc2;//这里的操作可以看做两步，1.pc = pc+1 2.pc = pc2,所以结果pc赋值为pc2：0x0022f53e
	//	(--pc) = pc2;//和自增操作移植，分为两部 1.pc = pc-1 2.pc = pc2所以结果pc赋值为pc2：0x0022f53e

	//	*(++pc) = c4[0];
	//	*(--pc) = c4[1];
	//	*(pc++) = c4[2];
	//	*(pc--) = c4[2];

	//	pc = pc + 1;
	//	pc = pc2;
	//	pc = pc3;
	//	//pc-- = pc2;
	//	//(pc++) = pc2;

		int a = 10, b = 20, c;
		c = a+++b;
		//c = a++++b;

	//}
}
void autoPtr() {
	auto_ptr<int> ptr1(new int(10));
	cout << *ptr1 << endl;

	auto_ptr<int> ptr2 = ptr1;
	cout << *ptr2 << endl;
	cout << *ptr1 << endl;

}
void uniquePtr() {
	unique_ptr<int> ptr1(new int(10));
	//unique_ptr<int> ptr2 = ptr1;error不能赋值
	//unique_ptr<int> ptr2(ptr1); //error不能拷贝
	unique_ptr<int> ptr2 = std::move(ptr1);

	cout << "ptr1:" << (ptr1 != nullptr ? *ptr1 : -1) << endl;
	cout << "ptr2:" << (ptr2 != nullptr ? *ptr2 : -1) << endl;
}
class B;
class A {
public:
	shared_ptr<B> pa;

	~A() {
		cout << "~A" << endl;
	}
};
class B {
public:
	weak_ptr<A> pb;

	~B() {
		cout << "~B" << endl;
	}
};
void sharedPtr() {
	shared_ptr<A> a(new A());
	shared_ptr<B> b(new B());
	cout << "第一次引用:" << endl;
	cout <<"计数a:" << a.use_count() << endl;
	cout << "计数b:" << b.use_count() << endl;
	a->pa = b;
	b->pb = a;
	cout << "第二次引用:" << endl;
	cout << "计数a:" << a.use_count() << endl;
	cout << "计数b:" << b.use_count() << endl;
}
void rename() {
	int a = 10;
	int& const rename_a = a;
	
	rename_a = 20;
	cout << "a:" << a << endl;
	cout << "rename_a:" << rename_a << endl;

	
}
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int& Add(int num1, int num2)
{
	int sum = num1 + num2;
	return sum;
}
int maxab(int a,int b) {
	return a > b ? a : b;
}
#include "extendsTest.h"
int  main()
{
	//maxab(3, 4);

	//Base tri;
	//tri.setWidth(1.0);
	//tri.setHeight(2.0);
	//double mul = tri.mulWH();
	//cout << mul << endl;

	//Base tri = new Triangel();
	
	extendsTest et;
	et.mainTest();

	return 0;
}
//int main()
//{
//   cout << "Hello World!\n";
//   //charBug();
//   /*int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
//   cout<<average(arr)<<endl;
//   vector<int> vec{ 1,2,3,4,5,6,7,8,9,10 };
//   cout << average2(vec) << endl;*/
//   //cast2();
//  /* externTest();
//   cout << maxbb(1, 2) << endl;*/
//   int a = 1, b = 2;
//   swap(a,b);
//   assert(a == 2 && b == 1);
//   return 1;
//}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
