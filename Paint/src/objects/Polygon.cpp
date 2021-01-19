#include "Polygon.h"
#include "../rendering/Shader.h"
namespace PaintSlayer {

	Polygon::Polygon(Shader& s) {
		this->mesh = Mesh();
		this->points = vector<Point>();
		this->color = std::array<float, 4>{1, 1, 1, 1};
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
		this->shader.setColor("icolor", this->color[0], this->color[1], this->color[2]);

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

	void Polygon::clear()
	{
		this->points.clear();
		this->mesh.vertices.clear();
		this->mesh.indices.clear();
	}

	void Polygon::terminate()
	{
		this->shader.terminate();
		this->mesh.terminate();
	}
	bool Polygon::isInside(Point point, vector<Point> polygone)
	{
		for (int i = 0; i < polygone.size(); i++)
		{
			if (point == polygone[i])
				return true;
		}
		return false;
	}
	vector<Point> Polygon::polyRectangle(vector<Point> polygone)
	{
		double xMin = std::numeric_limits<double>::max();
		double xMax = std::numeric_limits<double>::min();
		double yMin = std::numeric_limits<double>::max();
		double yMax = std::numeric_limits<double>::min();

		for (int i = 0; i < polygone.size(); i++)
		{
			double curX = polygone[i].getX();
			double curY = polygone[i].getY();

			if (xMax < curX)
				xMax = curX;
			else if (xMin > curY)
				xMin = curX;
			
			if (yMax < curY)
				yMax = curY;
			else if (yMin > curY)
				yMin = curY;
		}

		vector<Point> res;
		Point A(xMin, yMax);
		Point B(xMax, yMax);
		Point C(xMax, yMin);
		Point D(xMin, yMin);

		res.push_back(A);
		res.push_back(B);
		res.push_back(C);
		res.push_back(D);

		return res;
	}
}