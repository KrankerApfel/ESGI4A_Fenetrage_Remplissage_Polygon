#include "Polygon.h"

std::array<float, 4> Polygon::getColor() const
{
	return  this->color;
}

void Polygon::setColor(std::array<float, 4> c)
{
	this->color = c;
}

vector<Point> Polygon::getPoints() const
{
	return this->points;
}

void Polygon::addPoint(double x, double y)
{
	this->points.push_back(Point(x, y));
	this->mesh.addLastVertexAtPosition(x, y);

}

void Polygon::removePoint()
{
	this->points.pop_back();
	this->mesh.removeLastVertex();

}

void Polygon::draw(Shader& shader)
{
	this->mesh.draw(shader);
}

