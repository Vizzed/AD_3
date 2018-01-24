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
	int getBrGr();
	int getLaGr();
	int getBrMin();
	int getLaMin();
	double getBrSec();
	double getLaSec();
	double getBr();
	double getLa();
	//double operator-(const GEOKO &mid) const ;
	void setBrGr(int a);
	
};

