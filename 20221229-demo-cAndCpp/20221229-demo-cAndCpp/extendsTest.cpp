#include "extendsTest.h"
#include <string>
#include <iostream>
using namespace std;
class Father {
public:
	~Father() {
		cout << "~Father"<< endl;
	}
	//Father() {
	//	cout << "Father:" << name << endl;
	//}
	
	/*Father(string _name):name(_name){
		cout << "Father:" << name << endl;
	}*/
	string name = "father";
	int age = 45;
	void print() {
		cout << "name:" << name << " age:" << age << endl;
	}
};
class Son :public Father {
public:
	~Son() {
		cout << "~Son" << endl;
	}
	//Son(){
	//	cout << "Son:" << name << endl;
	//}
	/**/
	/*Son(string name):Father(name) {
		cout << "Son:" << name << endl;
	}*/
	string sex = "male";
	/*void print() {
		cout << "name:" << name << " age:" << age << " sex:" << sex << endl;
	}*/
};

class Complex {
public:
	Complex() {

	}
		double real, imag;
		Complex(double _real, double _imag):
			real(_real),imag(_imag)
		{
			cout << "real:" << real << " imag:" << imag << endl;
		}
		void print() {
			cout << "real:" << real << " imag:" << imag << endl;
		}
		Complex(const Complex& c) {
			real = c.real; imag = c.imag;
			cout << "complex copy" << endl;
		}
		//以全局函数的形式重载
		friend Complex operator+(const Complex& c1, const Complex& c2);
		//成员函数重载
		Complex& operator+=(const Complex& c);
};
Complex operator+(const Complex& c1, const Complex& c2) {
	Complex _c;
	_c.real = c1.real + c2.real;
	_c.imag = c1.imag + c2.imag;
	return _c;
}
Complex & Complex::operator+=(const Complex& c1) {
	this->real += c1.real;
	this->imag += c1.imag;
	return *this;
}

Complex func() {
	Complex c(1.0, 2.0);
	Complex c1(2.0, 3.0);
	c += c1;
	return c;
}

class A {
public:
	string name;
};
class B :public A {
public:
	int age;
};
class C :public A {
public:
	string sex;
};
class D :public B, public C {
public:
	int id;
};
//int main()
//{
//	D student;
//	student.name = "小明";
//	student.age = 18;
//	student.sex = "男";
//	student.id = 666;
//	return 0;
//}
class Geometry {
public:
	virtual void Draw() const=0;
};
class Circle :public Geometry{
public:
	void Draw() const{
		cout << "Circle draw" << endl;
	}
	int z;
};
class Rectangle :public Geometry {
public:
	void Draw() const{
		cout << "Rectangle draw" << endl;
	}
};
void extendsTest::mainTest()
{	
	Circle cir;
	const Geometry* e1 = &cir;
	e1->Draw();
	
};
