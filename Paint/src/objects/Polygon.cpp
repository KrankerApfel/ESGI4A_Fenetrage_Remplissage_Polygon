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
	vector<Point> Polygon::polyRectangle()
	{
		double xMin = std::numeric_limits<double>::max();
		double xMax = std::numeric_limits<double>::min();
		double yMin = std::numeric_limits<double>::max();
		double yMax = std::numeric_limits<double>::min();

		for (int i = 0; i < points.size(); i++)
		{
			double curX = points[i].getX();
			double curY = points[i].getY();

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
	void Polygon::fill(std::map<double, Maillion> SI)
	{
		for (auto it = SI.begin(); it != SI.end(); it++ )
		{
			float y1 = it->first;
			float x1 = it->second.xMin + it->second.coefDirInv;
			float x2;

			Maillion next = *(it->second.next);
			if ( &next != &Maillion::empty)
			{
				x2 = next.xMin + next.coefDirInv;
			}
			else {
				x2 = x1;
			}

			drawLine(x1, y1, x2, y1);	
			
		}

	}
	void Polygon::drawPoint(float x, float y)
	{
		glBegin(GL_POINTS);
		glColor3f(this->color[0], this->color[1], this->color[2]);
		glVertex2i(x, y);
		glEnd();
	}
	void Polygon::drawLine(float x1, float y1, float x2, float y2)
	{
		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
		dx = x2 - x1;
		dy = y2 - y1;
		dx1 = fabs(dx);
		dy1 = fabs(dy);
		px = 2 * dy1 - dx1;
		py = 2 * dx1 - dy1;
		if (dy1 <= dx1) {
			if (dx >= 0) {
				x = x1;
				y = y1;
				xe = x2;
			}
			else {
				x = x2;
				y = y2;
				xe = x1;
			}

			drawPoint(x, y);
			for (i = 0; x < xe; i++)
			{
				x++;
				if (px < 0) {
					px = px + 2 * dy1;
				}
				else {
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					{
						y++;
					}
					else
					{
						y--;
					}
					px = px + 2 * (dy1 - dx1);
				}
				drawPoint(x, y);
			}
		}
		else {
			if (dy >= 0) {
				x = x1;
				y = y1;
				ye = y2;
			}
			else {
				x = x2;
				y = y2;
				ye = y1;
			}

			drawPoint(x, y);
			for (i = 0; y < ye; i++)
			{
				y++;
				if (py <= 0) {
					py = py + 2 * dx1;
				}
				else {
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					{
						x++;
					}
					else
					{
						x--;
					}
					py = py + 2 * (dx1 - dy1);
				}
				drawPoint(x, y);
			}
		}
	}
}