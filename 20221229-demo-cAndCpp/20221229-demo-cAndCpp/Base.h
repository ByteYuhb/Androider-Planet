#pragma once
class Base
{
public:
	double getWidth();
	double getHeight();
	void setHeight(double height);
	void setWidth(double width);
	virtual double mulWH();
private:
	double width;
	double height;
};

