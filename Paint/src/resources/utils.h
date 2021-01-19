#pragma once
#include "../Objects/Point.h"
#include "../Objects/Polygon.h"
static double getDirCoef();
static Point* createSI(PaintSlayer::Polygon poly);
static vector<Point> SutherlandHodgman(vector<Point>& subjectPoints, vector<Point>& clippin_areaPoints );