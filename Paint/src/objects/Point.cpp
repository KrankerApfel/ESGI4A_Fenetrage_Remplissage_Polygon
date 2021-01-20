#include "Point.h"

Point::Point(double x, double y)
{
	this->_x = x;
	this->_y = y;
}

Point::Point()
{
	this->_x = 0;
	this->_y = 0;
}

double Point::getX() const  { return this->_x; }
double Point::getY() const { return this->_y; }
void Point::setX(const double x) { this->_x = x; }
void Point::setY(const double y) { this->_y = y; }
bool Point::operator==(const Point& A) const
{
	if (A.getX() == this->_x && A.getY() == this->_y)
		return true;
	return false;
}

bool Point::operator!=(const Point& A) const
{
	return !operator==(A);
}
