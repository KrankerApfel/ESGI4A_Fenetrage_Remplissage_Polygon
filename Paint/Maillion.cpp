#include "Maillion.h"

Maillion::Maillion(double _yMax, double _xMin, double _coefDirInv, Maillion* _next = nullptr)
{
		this->yMax = _yMax;
		this->xMin = _xMin;
		this->coefDirInv = _coefDirInv;
		this->next = _next;
}

Maillion::Maillion()
{
	this->yMax = 0;
	this->xMin = 0;
	this->coefDirInv = 0;
	this->next = &Maillion::empty;
}

Maillion Maillion::empty;