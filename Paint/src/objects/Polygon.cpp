#include "Polygon.h"
#include "../rendering/Shader.h"
namespace PaintSlayer {

	Polygon::Polygon(Shader& s) {
		this->mesh = Mesh();
		this->points = vector<Point>();
		this->color = std::array<float, 4>{1, 1, 1, 0};
		this->shader = s;
	}

	Polygon::Polygon(Shader& s, vector<Point>& p)
	{
		this->color = std::array<float, 4>{1, 1, 1, 0};

		this->mesh = Mesh();
		this->shader = s;
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
		this->shader.setColor("icolor", c[0], c[1], c[2]);

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

	void Polygon::draw()
	{
		this->shader.use();
		this->mesh.draw(this->shader);
	}

	Shader& Polygon::getShader() 
	{
		return this->shader;
	}


}