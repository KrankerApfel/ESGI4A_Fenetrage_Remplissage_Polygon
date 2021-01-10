#include "Point.h"

Point::Point(double x, double y)
{
	this->_x = x;
	this->_y = y;
}

double Point::getX() { return this->_x; }
double Point::getY() { return this->_y; }
void Point::setX(const double x) { this->_x = x; }
void Point::setY(const double y) { this->_y = y; }	