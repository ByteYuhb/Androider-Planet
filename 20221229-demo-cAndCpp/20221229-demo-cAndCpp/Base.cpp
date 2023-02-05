#include "Base.h"

double Base::getWidth() {
	return width;
}

double Base::getHeight() {
	return height;
}

void Base::setWidth(double widht) {
	this->width = width;
}

void Base::setHeight(double height) {
	this->height = height;;
}

double Base::mulWH() {
	return width * height;
}
