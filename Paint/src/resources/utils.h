#pragma once
#include "../Objects/Point.h"
#include "../Objects/Polygon.h"
#include "../../Maillion.h"
#include <vector>
#include <map>


double getDirCoef(const Point& a, const Point& b);
vector<Point> SutherlandHodgman(const vector<Point>& subjectPoints,const vector<Point>& clippin_areaPoints);
Point getIntersection(Point& d1Start, Point& d1End, Point& d2Start, Point& d2end);
bool isPointInsidePoligon(Point pt, std::vector<Point> points);
std::map<double, Maillion> initStructureSI(PaintSlayer::Polygon p);
Maillion computeMaillion(Point& p1, Point& p2);
std::vector<Point> orderPointByY(std::vector<Point>& points);
bool visible(Point& pt, Point& A, Point& B);



