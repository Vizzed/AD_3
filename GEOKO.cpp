#include "GEOKO.h"



GEOKO::GEOKO() :brGr(0), brMin(0),brSec(0),laGr(0),laMin(0),laSec(0)
{
}
GEOKO::GEOKO(int brGr, int laGr, int brMin, int laMin, double brSec, double laSec,double br,double la) {
	this->brGr = brGr;
	this->brMin = brMin;
	this->brSec = brSec;
	this->laGr = laGr;
	this->laMin = laMin;
	this->laSec = laSec;
	this->br = br;
	this->la = la;
}

GEOKO::~GEOKO()
{
}

int GEOKO::getBrGr()
{
	return brGr;
}

int GEOKO::getLaGr()
{
	return laGr;
}

int GEOKO::getBrMin()
{
	return brMin;
}

int GEOKO::getLaMin()
{
	return laMin;
}

double GEOKO::getBrSec()
{
	return brSec;
}

double GEOKO::getLaSec()
{
	return laSec;
}

double GEOKO::getBr()
{
	return br;
}

double GEOKO::getLa()
{
	return la;
}
/*
double GEOKO::operator-(const GEOKO &mid) const
{ 
	double abstand;
		abstand = sqrt(pow(br - mid.getBr(), 2) + pow(la - mid->getLa(), 2));
	return abstand;
}
*/
void GEOKO::setBrGr(int a)
{
	this->brGr = a;
}

