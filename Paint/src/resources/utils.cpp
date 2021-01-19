#include "utils.h"


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
	
	}
	return SutherlandHodgman(clippedPoints, clipping_areaPoints, ++iterator);
}
