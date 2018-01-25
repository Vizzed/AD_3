#pragma once
#include "DVKE.h"
#include "GEOKO.h"
#include <fstream>
#include <string>
#include <sstream>
#define maxi 1000000
using namespace std;

class DVK
{
private:
	GEOKO* ankerV;
	GEOKO* ankerR;
	GEOKO* middle;
	GEOKO* index[maxi];
	int anz;
public:
	DVK(int anz,string choice);
	DVK();
	~DVK();
	int getAnz();
	GEOKO* getMiddle();
	GEOKO** indexCopy();
	void quickSort(int links, int rechts, GEOKO* index_neu[]);
	double distance(GEOKO* geoko);
	void inDateiSchreiben(string dat,GEOKO* index_neu[]);

	void SelectionSort(GEOKO* index_neu[]);

	void swap(int i, int zeiger, GEOKO * Arr[]);
	
	void writeListe(GEOKO * arr[], int anz, const  string name);
};

