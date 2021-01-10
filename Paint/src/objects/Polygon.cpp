#include "Polygon.h"
namespace PaintSlayer {

	Polygon::Polygon() {
		this->mesh = Mesh();
		this->points = vector<Point>();
		this->color = std::array<float, 4>{1, 1, 1, 0};
	}

	Polygon::Polygon(vector<Point>& p)
	{
		this->color = std::array<float, 4>{1, 1, 1, 0};

		this->mesh = Mesh();

		this->points = p;
		this->color = std::array<float, 4>{1, 1, 1, 0};

		for (int i = 0; i < p.size(); i++)
		{
			addPoint(p.at(i).getX(), p.at(i).getY());

		}
	}

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


}