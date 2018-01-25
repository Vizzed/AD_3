#include "DVK.h"
#include <iostream>
#include "algorithm"
#include "iomanip"

DVK::DVK()
{
}

DVK::DVK(int anz,string choice){
	
	double xb,xl;
	double br_ges=0, la_ges=0;
	this->anz = anz;	
	ifstream file(choice);
	double br,la,brSec,laSec;
	string zeile;
	int brGr, brMin, laGr, laMin;
	for (int i = 0; i < anz; i++)
	{
		getline(file, zeile, ',');	//lese eine Zeile bis zum Komma 
//s.erase(std::remove(s.begin(), s.end(), ' '), s.end());//https://www.c-plusplus.net/forum/265080-full
		br = stod(zeile);	//Umwandeln des Stringwertes in ein Double
		getline(file, zeile, ';');	// lese die Zeile bis zum Simikolon					
		la = std::stod(zeile);
		//Umrechnung von Dezimalgrad in Zeitkoordinaten
		//http://www.mwegner.de/geo/geo-koordinaten/umrechnung-grad-minute-sekunde-dezimalgrad.html
		brGr = (int)(br/3600);
		laGr = (int)(la/3600);

		xb = (br/3600 - brGr) * 60;
		xl = (la/3600 - laGr) * 60;

		brMin = (int)xb;
		laMin = (int)xl;
		
		brSec = (double)((xb - brMin) * 60);
		laSec = (double)((xl  - laMin) * 60);
		GEOKO* temp = new GEOKO(brGr, laGr, brMin, laMin, brSec, laSec,br,la);
		//breite und laenge Gesamt(für middle Berechnung)
		br_ges += br;
		la_ges += la;

		index[i] = temp;
		
		//ankerV setzten
		if (i==0) {
			this->ankerV = temp;
		}
		//Verkettung der Objekte durch setN und setV
		if ((i!=0)&&(i<anz-1))
		{
			this->index[i - 1]->setN(temp);
			this->index[i]->setV(index[i - 1]);
		}
		//ankerR setzten
		if (i == anz - 1) {
			this->ankerR = index[i];
		}
		
	}

	//Teilen der Gesamtbreite-laenge durch Anzahl
	br_ges /= this->anz;
	la_ges /= this->anz;
	brGr = (int)(br_ges / 3600);
	laGr = (int)(la_ges / 3600);
	xb = (br_ges / 3600 - brGr) * 60;
	xl = (la_ges / 3600 - laGr) * 60;
	brMin = (int)xb;
	laMin = (int)xl;

	brSec = (double)((xb - brMin) * 60);
	laSec = (double)((xl - laMin) * 60);
	this->middle = new GEOKO(brGr, laGr, brMin, laMin, brSec, laSec, br, la);
	file.close();


}



DVK::~DVK()
{
}


int DVK::getAnz()
{
	return anz;
}


GEOKO* DVK::getMiddle()
{
	return middle;
}

GEOKO** DVK::indexCopy()
{
	GEOKO** index_neu = new GEOKO*[anz];

	for (int i = 0; i < anz; i++) {
		index_neu[i] = index[i];
	}
	//index_neu[0].setBrGr(1);
	//cout << index_neu[0].getBrGr()<<endl;
	return index_neu;
}

void DVK::quickSort(int links,int rechts,GEOKO* index_neu[])
{
	int pivot = links;
	int tausch;
	
	for (int i = links + 1; i <= rechts; i++) {
	
		if (*index_neu[pivot] >> *middle > *index_neu[i] >> *middle)	//tausche pivot mit Element wenn Element kleiner
		{
			tausch = i;
			while (pivot < tausch) {							//tauschen
				GEOKO* temp = index_neu[tausch];
				index_neu[tausch] = index_neu[tausch - 1];
				index_neu[tausch - 1] = temp;
				tausch--;
			}
			pivot++;
		}
	}
	if (links < pivot - 1) {
		quickSort(links, pivot - 1,index_neu);
	}
	if (rechts > pivot + 1) {
		quickSort(pivot + 1, rechts,index_neu);
	}
	
}


double DVK::distance(GEOKO* geoko)
{
	double distance = sqrt(pow(geoko->getBr() -this->middle->getBr(), 2) + pow(geoko->getLa()-this->middle->getLa(), 2));
	return distance;
}

void DVK::inDateiSchreiben(string dat,GEOKO* index_neu[])
{
	
	ofstream datei(dat);
	for (int i = 0; i < anz; i++) {
		// Rausschreiben mit 2 Nachkommastellen
		datei << std::fixed << setprecision(2) << index_neu[i]->getBr() << ": " << index_neu[i]->getLa() << ";" << " Abstand zum Mittelpunkt: " << (*middle>>*index_neu[i])<< endl;
	}
	datei.close();
}

GEOKO * DVK::getMiddle() const
{
	return this->middle;
}

void DVK::SelectionSort(GEOKO* index_neu[]) {
	
	int zeiger = 0;
	int anz = this->anz;
	GEOKO* start = NULL;

	for (int i = 0; i < this->anz; i++) {
		zeiger = i;
		start = index_neu[i];

		for (int k = zeiger+1; k < anz ; k++) {
			if (*index_neu[k]>>*middle > *index_neu[zeiger]>>*middle) {
			//if (distance(index_neu[k]) < distance(index_neu[zeiger])){
				zeiger = k;
			}
		}
		index_neu[i] = index_neu[zeiger];
		index_neu[zeiger] = start;
		//swap(zeiger, (anz - i), index_neu);
	}
	
}

void DVK::swap(int i, int zeiger, GEOKO *Arr[]) {
	GEOKO *tmp = Arr[i];
	Arr[i] = Arr[zeiger];
	Arr[zeiger] = tmp;
}

void DVK::writeListe(GEOKO * arr[], int anz, const  string name) {
	double br, la;
	ofstream datei(name);
	for (int i = 0; i < anz; i++) {
		br= (((arr[i]->getBrSec() / 60) + arr[i]->getBrMin()) / 60) + arr[i]->getBrGr();
		la= (((arr[i]->getLaSec() / 60) + arr[i]->getLaMin()) / 60) + arr[i]->getLaGr();
		// Rausschreiben mit 2 Nachkommastellen
		datei << std::fixed << setprecision(2) << "   " << br << ",   " << la << ";" << endl;
	}
	datei.close();
}