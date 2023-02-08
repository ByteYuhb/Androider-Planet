#include "FIleTest.h"
#include <fstream>
#include <iostream>
using namespace std;

class Person {

public :
	string m_name;
	int age;
	~Person() {
		cout << m_name << endl;
	}
};
void writeFile(string filename) {
	//二进制文件
	ofstream ofs1;
	ofs1.open(filename, ios::out | ios::binary);
	if (!ofs1.is_open()) {
		return;
	}
	Person per = { "123",10 };

	ofs1.write((const char*)&per, sizeof(Person));
	ofs1.close();
}
void readFile(string filename) {
	ifstream ifs1(filename, ios::in);
	Person per1;
	ifs1.read((char*)&per1, sizeof(Person));

	cout << per1.m_name << ":" << per1.age << endl;

	ifs1.close();
}
void FIleTest::main() {
	//文本文件
	/*ofstream ofs;
	ofs.open("file.txt", ios::out);
	ofs.write("1234",4);
	ofs << "nihao" << endl;
	ofs.close();

	ifstream ifs("file.txt");
	char buf[100] = { 0 };

	ifs >> buf;
	cout << buf << endl;

	while (ifs.getline(buf, sizeof(buf))) {
		cout << buf << endl;
	}

	ifs.close();*/

	writeFile("file1.txt");
	readFile("file1.txt");
	
}
