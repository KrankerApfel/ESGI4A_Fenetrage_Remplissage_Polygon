#include "utils.h"
#include <limits>
#include<algorithm> 

double getDirCoef(const Point& a,const  Point& b)
{
	return (b.getX() - a.getX())*(b.getY() - a.getY());
}

Point* createSI(PaintSlayer::Polygon poly)
{
	vector<Point> points = poly.polyRectangle();
	return nullptr;
}

vector<Point> SutherlandHodgman(const vector<Point>& subjectPoints, const vector<Point>& clipping_areaPoints, int iterator)
{
	if (iterator == clipping_areaPoints.size() - 1) return subjectPoints;

	vector<Point> points = subjectPoints;
	vector<Point> clippedPoints = subjectPoints;
	clippedPoints.clear();
	for (int i = 0; i < points.size(); i++) {
		Point pt_current = points.at(0);
		Point pt_previous = points.at((static_cast<unsigned long long>(i)-1) % points.size());
		Point pt_A = clipping_areaPoints.at(iterator);
		Point pt_B = clipping_areaPoints.at(static_cast<std::vector<Point, std::allocator<Point>>::size_type>(iterator)+1);
		
		Point pt_intersection = getIntersection(pt_previous, pt_current, pt_A, pt_B );
		if (isPointInsidePoligon(pt_current, clipping_areaPoints))
		{
			if(!isPointInsidePoligon(pt_previous, clipping_areaPoints)) clippedPoints.push_back(pt_intersection);
			clippedPoints.push_back(pt_current);
		}
		else if (isPointInsidePoligon(pt_previous, clipping_areaPoints)) 
		{
			clippedPoints.push_back(pt_intersection);
		}
	}
	return SutherlandHodgman(clippedPoints, clipping_areaPoints, ++iterator);
}

Point getIntersection(Point& d1Start, Point& d1End, Point& d2Start, Point& d2end)
{
	double a1 = d1End.getY() - d1Start.getY();
	double b1 = d1Start.getX() - d1End.getX();
	double c1 = a1 * (d1Start.getX()) + b1 * (d1Start.getY());

	double a2 = d2end.getY() - d2Start.getY();
	double b2 = d2Start.getX() - d2end.getX();
	double c2 = a2 * (d2Start.getX()) + b2 * (d2Start.getY());

	double determinant = a1 * b2 - a2 * b1;

	if (determinant == 0)
		return Point(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());

	double x = (b2 * c1 - b1 * c2) / determinant;
	double y = (a1 * c2 - a2 * c1) / determinant;
	return Point(x, y);

}

bool isPointInsidePoligon(Point pt, std::vector<Point> points)
{
	bool intersections = false;
	int size = points.size();
	int j = size - 1;
	for (int i = 0; i <size; i++)
	{
		if ((points.at(i).getY() > pt.getY()) != (points.at(j).getY() > pt.getY())
			&& (pt.getX() < points.at(i).getX() + (points.at(j).getX() - points.at(i).getX()) * (pt.getY() - points.at(i).getY()) /	(points.at(j).getY() - points.at(i).getY())
			))
		{
			intersections = !intersections;
		}
		j = i;

	}

	return intersections;
}

std::map<int, std::vector<Maillion>> initStructureSI(PaintSlayer::Polygon p)
{
	std::map<int, std::vector<Maillion>> SI; 
/*	std::vector<Point> rectBoundPoints = p.polyRectangle();
	
	for (int i = rectBoundPoints.at(2).getY(); i < rectBoundPoints.at(1).getY(); i++)
	{
		std::vector<Maillion> m{ Maillion()};
		SI.insert({ i,m });
	}*/

	std::vector<Point> points_orderByY = orderPointByY(p.getPoints());

	return SI;
}

Maillion computeMaillion(Point& p1, Point& p2)
{
	double yMin = std::min(p1.getY(), p2.getY());
	double xOfYMin;
	if (yMin == p1.getY()) xOfYMin = p1.getX();
	else xOfYMin = p2.getX();
	return Maillion
	{
		std::max(p1.getY(), p2.getY()),// yMax
		xOfYMin,// x du yMin
		1 / getDirCoef(p1,p2), // inverse slope
		nullptr // next
	};
}

std::vector<Point> orderPointByY(std::vector<Point>& points)
{
	std::vector<Point> res;

	for (int i = 0; i < points.size(); i++)
	{
		
	}
	return res;
}

