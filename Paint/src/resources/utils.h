#pragma once
#include "../Objects/Point.h"
#include "../Objects/Polygon.h"
#include <vector>
#include <map>
class Maillion {
public :
	double yMax;
	double xMin; // x du yMin
	double coefDirInv;
	Maillion next;

	Maillion(double _yMax, double _xMin, double _coefDirInv, Maillion& _next)
	{
		this->yMax = _yMax;
		this->xMin = _xMin;
		this->coefDirInv = _coefDirInv;
		this->next = _next;
	}
	Maillion& operator=(Maillion& m)
	{
		this->yMax = m.yMax;
		this->xMin = m.xMin;
		this->coefDirInv = m.coefDirInv;
		this->next = m.next;
	}
};

double getDirCoef(const Point& a, const Point& b);
Point* createSI(PaintSlayer::Polygon poly);
vector<Point> SutherlandHodgman(const vector<Point>& subjectPoints,const vector<Point>& clippin_areaPoints, int iterator);
Point getIntersection(Point& d1Start, Point& d1End, Point& d2Start, Point& d2end);
bool isPointInsidePoligon(Point pt, std::vector<Point> points);
std::map<double, Maillion> initStructureSI(PaintSlayer::Polygon p);
Maillion computeMaillion(Point& p1, Point& p2);
std::vector<Point> orderPointByY(std::vector<Point>& points);