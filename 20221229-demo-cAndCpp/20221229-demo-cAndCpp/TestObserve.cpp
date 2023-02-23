#include "TestObserve.h"
#include "Observer.h"
#include "Subject.h"
#include <iostream>
using namespace std;
class User1 :public Observer {
	void update(void* pArgs)const{
		cout << "User1:" << (const char*)pArgs << endl;
	}
};
class User2:public Observer {
	void update(void* pArgs)const {
		const char* c = (const char*)pArgs;
		cout << "User2:" << (const char*)pArgs << endl;
	}
};
void TestObserve::test() {
	User1* user1 = new User1();
	User2* user2 = new User2();
	Subject* sub = new Subject();
	cout << "begin add Observer" << endl;
	sub->addObserve(user1);
	sub->addObserve(user2);

	cout << "begin notify Observer" << endl;
	
	string s("send success!");
	
	sub->notify((void*)s.c_str());

}
