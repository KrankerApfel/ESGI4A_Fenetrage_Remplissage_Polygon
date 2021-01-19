#pragma once
#include "../Objects/Point.h"
#include "../Objects/Polygon.h"
double getDirCoef();
Point* createSI(PaintSlayer::Polygon poly);
vector<Point> SutherlandHodgman(vector<Point>& subjectPoints, vector<Point>& clippin_areaPoints, int iterator);
Point getIntersection(Point d1Start, Point d1End, Point d2Start, Point d2end);