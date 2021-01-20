#pragma once
class Maillion {
	public:
		double yMax;
		double xMin; // x du yMin
		double coefDirInv;
		Maillion *next;
		Maillion(double _yMax, double _xMin, double _coefDirInv, Maillion* _next);
		Maillion();
		Maillion& operator=(Maillion& m)
		{
			this->yMax = m.yMax;
			this->xMin = m.xMin;
			this->coefDirInv = m.coefDirInv;
			this->next = m.next;

			return *this;
		}
		static Maillion empty;




};