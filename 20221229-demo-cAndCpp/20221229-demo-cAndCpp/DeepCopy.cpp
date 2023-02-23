#include "DeepCopy.h"
#include <iostream>
#include <string>
using namespace std;
//引用计数方式
//class Human {
//public:
//	Human(int age):_age(age) {
//		
//	}
//	int _age;;
//};
//class String {
//public:
//	String() {
//		addRefCount();
//	}
//	String(Human* pHuman){
//		this->pHuman = pHuman;
//		addRefCount();
//	}
//	//重写拷贝构造，实现深拷贝，防止二次释放内存引发崩溃
//	String(const String& str) {
//		////深拷贝
//		//pHuman = new Human(str.pHuman->_age);
//		//浅拷贝
//		pHuman = str.pHuman;
//		addRefCount();
//	}
//	~String() {
//		subRefCount();
//		if (getRefCount() <= 0) {
//			delete pHuman;
//		}	
//	}
//	Human* pHuman;
//private:
//	void addRefCount() {
//		refCount++;
//	}
//	void subRefCount() {
//		refCount--;
//	}
//	int getRefCount() {
//		return refCount;
//	}
//	static int refCount;
//};
//int String::refCount = 0;
//void DeepCopy::main() 
//{	
//	Human* p = new Human(100);
//	String s1(p);
//	String s2 = s1;
//
//}

//移动语义move
class Human {
public:
	Human(int age) :_age(age) {

	}
	int _age;;
};
class String {
public:

	String(Human* pHuman) {
		this->pHuman = pHuman;
	}
	//重写拷贝构造，实现深拷贝，防止二次释放内存引发崩溃
	String(const String& str) {
		////深拷贝
		//pHuman = new Human(str.pHuman->_age);
		//浅拷贝
		pHuman = str.pHuman;
	}
	//移动构造函数
	String(String&& str) {
		pHuman = str.pHuman;
		str.pHuman = NULL;
	}

	~String() {
		if (pHuman != NULL) {
			delete pHuman;
		}		
	}
	Human* pHuman;	
};
void DeepCopy::main()
{
	Human* p = new Human(100);
	String s1(p);

	String s2(std::move(s1));

	String s3(std::move(s2));

}
