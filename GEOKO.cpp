#include "GEOKO.h"



GEOKO::GEOKO() :brGr(0), brMin(0), brSec(0), laGr(0), laMin(0), laSec(0), br(0), la(0) {
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

int GEOKO::getBrGr() const
{
	return brGr;
}

int GEOKO::getLaGr()const
{
	return laGr;
}

int GEOKO::getBrMin()const
{
	return brMin;
}

int GEOKO::getLaMin()const
{
	return laMin;
}

double GEOKO::getBrSec()const
{
	return brSec;
}

double GEOKO::getLaSec()const
{
	return laSec;
}

double GEOKO::getBr() const
{
	return br;
}

double GEOKO::getLa()const
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

double GEOKO::operator>>(const GEOKO& Vergl) const {
	double tBr, VBr, tLa, VLa;
	GEOKOtoDouble(this, &tBr, &tLa);
	GEOKOtoDouble(&Vergl, &VBr, &VLa);
	return sqrt(pow(tBr - VBr, 2) + pow(tLa - VLa, 2));
}
void GEOKO::GEOKOtoDouble(const GEOKO * G, double *Br, double *La) const {
	*Br = (double)(G->getBrGr() * 3600) + (double)(G->getBrMin() * 60) + (G->getBrSec());
	*La = (double)(G->getLaGr() * 3600) + (double)(G->getLaMin() * 60) + (G->getLaSec());
}
