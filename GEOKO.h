#pragma once
#include "DVKE.h"
#include <math.h>
class GEOKO:public DVKE{
private:
	int brGr;
	int laGr;
	int brMin;
	double brSec;
	int laMin;
	double laSec;
	double br, la;
public:
	GEOKO();
	GEOKO(int brGr, int laGr, int brMin, int laMin, double brSec, double laSec,double br,double la);
	~GEOKO();
	int getBrGr()const;
	int getLaGr()const;
	int getBrMin()const;
	int getLaMin()const;
	double getBrSec()const;
	double getLaSec()const;
	double getBr()const;
	double getLa()const;
	//double operator-(const GEOKO &mid) const ;
	void setBrGr(int a);

	double operator>>(const GEOKO & Vergl) const;

	void GEOKOtoDouble(const GEOKO * G, double * Br, double * La) const;
	
};

