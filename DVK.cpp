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
	br_ges /= anz;
	la_ges /= anz;
	brGr = (int)(br_ges / 3600);
	laGr = (int)(la_ges / 3600);
	xb = (br_ges / 3600 - brGr) * 60;
	xl = (la_ges / 3600 - laGr) * 60;
	brMin = (int)xb;
	laMin = (int)xl;

	brSec = (double)((xb - brMin) * 60);
	laSec = (double)((xl - laMin) * 60);
	middle = new GEOKO(brGr, laGr, brMin, laMin, brSec, laSec, br, la);
	file.close();


}



DVK::~DVK()
{
}

GEOKO * DVK::listeAusgeben()
{
	return ankerV;
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
	GEOKO** index_neu;
	index_neu = new GEOKO*[anz];
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

		if ((distance(index_neu[pivot]))>(distance(index_neu[i])))	//tausche pivot mit Element wenn Element kleiner
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
		quickSort(links, pivot - 1, index_neu);
	}
	if (rechts > pivot + 1) {
		quickSort(pivot + 1, rechts, index_neu);
	}
	
	ofstream datei("Daten_S.csv");
	for (int i = 0; i < anz; i++) {
		// Rausschreiben mit 2 Nachkommastellen
		datei << std::fixed << setprecision(2)<< index_neu[i]->getBr() << ": " << index_neu[i]->getLa() << ";"<<" Abstand zum Mittelpunkt: " <<distance(index_neu[i])<< endl;
	}
	datei.close();
}

double DVK::distance(GEOKO* geoko)
{
	double distance = sqrt(pow(geoko->getBr() -middle->getBr(), 2) + pow(geoko->getLa()-middle->getLa(), 2));
	return distance;
}

