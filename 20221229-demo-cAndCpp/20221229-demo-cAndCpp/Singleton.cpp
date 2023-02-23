#include "Singleton.h"
#include <iostream>

using namespace std;

Singleton* Singleton::instance = nullptr;
Singleton* Singleton::getInstance() {
	if (instance == nullptr) {
		instance = new Singleton();
	}
	return instance;
}
void Singleton::doSomething() {
	cout << "I am yuhb!" << endl;
}




