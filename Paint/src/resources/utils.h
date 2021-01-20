#pragma once
#include "../Objects/Point.h"
#include "../Objects/Polygon.h"
#include <vector>
#include <map>
typedef struct Maillion {
	int yMax;
	float xMin; // x du yMin
	float coefDirInv;
	Maillion* next;
};

double getDirCoef(const Point& a, const Point& b);
Point* createSI(PaintSlayer::Polygon poly);
vector<Point> SutherlandHodgman(const vector<Point>& subjectPoints,const vector<Point>& clippin_areaPoints, int iterator);
Point getIntersection(Point& d1Start, Point& d1End, Point& d2Start, Point& d2end);
bool isPointInsidePoligon(Point pt, std::vector<Point> points);
std::map<int, std::vector<Maillion>> initStructureSI(PaintSlayer::Polygon p);
Maillion computeMaillion(Point& p1, Point& p2);
