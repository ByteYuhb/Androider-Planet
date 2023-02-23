#pragma once
#include <iostream>

class Observer
{
public:
	virtual void update(void* pArgs)const {};
};

