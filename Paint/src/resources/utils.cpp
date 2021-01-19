#include "utils.h"
#include <limits>

double getDirCoef()
{
	return 0.0;
}

Point* createSI(PaintSlayer::Polygon poly)
{
	return nullptr;
}

vector<Point> SutherlandHodgman(vector<Point>& subjectPoints, vector<Point>& clipping_areaPoints, int iterator)
{
	if (iterator == clipping_areaPoints.size()) return subjectPoints;

	vector<Point> clippedPoints = subjectPoints;
	for (int i = 0; i < clippedPoints.size(); i++) {
		// récupé
		//Point intersection = getIntersection();
		//if intersection.getX() == std::numeric_limits<double>::max() && intersection.getY() == std::numeric_limits<double>::max()
	}
	return SutherlandHodgman(clippedPoints, clipping_areaPoints, ++iterator);
}

Point getIntersection(Point d1Start, Point d1End, Point d2Start, Point d2end)
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
