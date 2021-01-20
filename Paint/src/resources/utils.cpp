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

std::map<double, Maillion> initStructureSI(PaintSlayer::Polygon p)
{
	std::vector<Point> points_orderByY = p.getPoints();
	std::map<double,Maillion> SI; 

	points_orderByY = orderPointByY(points_orderByY);
	int size = points_orderByY.size();
	Point current, previous, next;

	for (int i = 0; i < size; i++)
	{
		// les trois points des segment traité
		current = points_orderByY.at(i);
		previous = points_orderByY.at((i - 1) % size);
		next = points_orderByY.at((i + 1) % size);
		
		if (previous.getY() > current.getY())
		{
			Maillion m = computeMaillion(current, previous);
			if (next.getY() > current.getY()) {
				Maillion n = computeMaillion(current, next);
				m.next = n;
			}			
			SI.insert_or_assign(current.getY(), m);
		}
		else if (next.getY() > current.getY()) {
			Maillion m = computeMaillion(current, next);
			SI.insert_or_assign(current.getY(), m);
		}	
	}

	// rajouter les trous dans la structure SI
	for (auto it = SI.begin(); it != SI.end(); ++it)
	{
		auto it_next = it;
		it_next++;
		// si les nombres ne sont pas successive
		double diff = abs(it->first - it_next->first);
		if (diff > 1)
		{
			double step = 0.001;
			for (double i = it->first + step; i < it_next->first; i + step)
			{
				SI.insert_or_assign(i, nullptr);
			}
		}		
	}	

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

std::vector<Point> orderPointByY(std::vector<Point> &points)
{
	std::vector<Point> res = points;
	Point tmp(0,0);

	for (int i = 0; i < points.size()-1; i++)
	{
		for (int j = 0; j < points.size()-1; j++)
		{
			if (res[j].getY() > res[j + 1].getY())
			{
				tmp = res[j+1];
				res[j + 1] = res[j];
				res[j] = tmp;
			}
		}
	}
	return res;
}

