#pragma once
#include "Base.h"
class Rectangel:Base
{
public:
	double mulWH() {
		return getWidth() * getHeight();
	}
};

