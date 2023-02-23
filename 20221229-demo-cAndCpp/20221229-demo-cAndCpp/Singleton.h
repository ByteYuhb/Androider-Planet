#pragma once
class Singleton
{
public:
	static Singleton* getInstance();
	static void doSomething();
private:
	static Singleton* instance;
};

