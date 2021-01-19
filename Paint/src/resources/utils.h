#pragma once
#include "../Objects/Point.h"
#include "../Objects/Polygon.h"
double getDirCoef();
Point* createSI(PaintSlayer::Polygon poly);
vector<Point> SutherlandHodgman(const vector<Point>& subjectPoints,const vector<Point>& clippin_areaPoints, int iterator);
Point getIntersection(Point& d1Start, Point& d1End, Point& d2Start, Point& d2end);
bool isPointInsidePoligon(Point pt, std::vector<Point> points);