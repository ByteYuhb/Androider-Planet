#pragma once
#include "Base.h"
class Triangel:Base
{
public:
	double mulWH() {
		return getWidth() * getHeight() / 2;
	}
	Triangel();
	~Triangel();
	
};

