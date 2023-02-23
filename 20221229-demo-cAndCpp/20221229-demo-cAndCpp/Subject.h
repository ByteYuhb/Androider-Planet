#pragma once
#include <list>
#include "Observer.h"

class Subject
{
public:
	void _addObserve(Observer& obs);
	void addObserve(Observer* obs);
	void notify(void* pArg);
private:
	std::list<Observer*> _list;
};

