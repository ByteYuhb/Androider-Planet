#include "DeepCopy.h"
#include <iostream>
#include <string>
using namespace std;
//���ü�����ʽ
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
//	//��д�������죬ʵ���������ֹ�����ͷ��ڴ���������
//	String(const String& str) {
//		////���
//		//pHuman = new Human(str.pHuman->_age);
//		//ǳ����
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

//�ƶ�����move
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
	//��д�������죬ʵ���������ֹ�����ͷ��ڴ���������
	String(const String& str) {
		////���
		//pHuman = new Human(str.pHuman->_age);
		//ǳ����
		pHuman = str.pHuman;
	}
	//�ƶ����캯��
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
