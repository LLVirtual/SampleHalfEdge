#ifndef CPOINT_H_INCLUDED
#define CPOINT_H_INCLUDED

#include <assert.h>
#include <math.h>

class Point
{
	public:
		Point();
		~Point();
		double x;
		double y;
		double z;
	private:

};

///<summary>
///TODO 暂时不考虑其他的运算 只是用于显示，后续会逐渐修改
///</summary>
Point::Point()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Point::~Point()
{

}

#endif
