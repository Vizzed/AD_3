
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "DVK.h"
#include "algorithm"
#include "iomanip"
#include <conio.h>
#include <string.h>
#include "windows.h"
#include "math.h"
using namespace std;
void beginMessung(LONGLONG *g_LastCount, LONGLONG *g_FirstCount, LONGLONG *g_Frequency, double *nulltime) {

	//----------------------------------------------------------------------
	//
	//    Zeitmessung im æs-Bereich
	//    TESTANWENDUNG
	//    Author: tbird
	//    Date: 20.11.2007
	//
	//----------------------------------------------------------------------

	// Variablen
	LONGLONG g_FirstNullCount, g_LastNullCount;

	// Frequenz holen
	if (!QueryPerformanceFrequency((LARGE_INTEGER*)g_Frequency))
		printf("Performance Counter nicht vorhanden");

	double resolution = 1000000 / ((double)*g_Frequency);

	printf("Frequenz des Counters:  %lld kHz\n", *g_Frequency / 1000);  //lld -> LONGLONG darstellung
	printf("Dadurch maximale Aufloesung: %4.5f us\n", resolution);

	// null-messung
	QueryPerformanceCounter((LARGE_INTEGER*)&g_FirstNullCount);
	QueryPerformanceCounter((LARGE_INTEGER*)&g_LastNullCount);
	*nulltime = (((double)(g_LastNullCount - g_FirstNullCount)) / ((double)*g_Frequency));

	printf("Null-Zeit: %4.5f us\n", *nulltime * 1000000);

	// beginn messung
	QueryPerformanceCounter((LARGE_INTEGER*)g_FirstCount);
}

void endeMessung(LONGLONG g_LastCount, LONGLONG g_FirstCount, LONGLONG g_Frequency, double nulltime) {

	// 2. Messung
	QueryPerformanceCounter((LARGE_INTEGER*)&g_LastCount);

	double dTimeDiff = (((double)(g_LastCount - g_FirstCount)) / ((double)g_Frequency));

	// Von der gemessenen Zeit die "Null-Zeit" abziehen, um genauer zu werden
	double time = (dTimeDiff - nulltime) * 1000000; //mikro-sekunden
	printf("Zeit: %4.5f us\n", time);
}

int main() {
	
	int choice;
	int anz;
	int datei=0;
	DVK* dvk=nullptr;
	GEOKO* geoko=nullptr;
	DVKE* dvke=nullptr;
	string file;
	
	do{
		cout << "Menue:" << endl;
		cout << "'1' Verkettete Liste erzeugen." << endl;
		cout << "'2' Quicksort." << endl;
		cout << "'3' anderes Sortieralgortihmus." << endl;
		cout << "'4' Programm beenden." << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Geben Sie ein wieviele Objekte erstellt werden sollen (weniger als 1000000)" << endl;
			cin >> anz;
			if (anz > 1000000) {
				cout << "Zu grosse Zahl." << endl;
				break;
			}

				while ((datei!=2)&&(datei!=1))
				{
					cout << "Um Datei zu oeffnen druecken Sie '1' oder fuer Datei1 '2'" << endl;
					cin >> datei;
					switch (datei)
					{
					case 1:
						file = "Daten.csv";
						break;
					case 2:
						file = "Daten1.csv";
						break;
					default:cout << "Ungueltige Eingabe";
						break;
					}
				} 
				dvk = new DVK(anz, file);
				printf("MittelKoordinate betraegt: %i:%i:%f  %i:%i:%f\n ", dvk->getMiddle()->getBrGr(), dvk->getMiddle()->getBrMin(), dvk->getMiddle()->getBrSec(), dvk->getMiddle()->getLaGr(), dvk->getMiddle()->getLaMin(), dvk->getMiddle()->getLaSec());
				cout<< std::fixed << setprecision(2) << dvk->getMiddle()->getBr() << ":"<< dvk->getMiddle()->getLa()<< endl;
				dvk->indexCopy();
				
				break;
		case 2:{ 
			GEOKO** copy = dvk->indexCopy();
			LONGLONG g_Frequency = 0, g_FirstCount = 0, g_LastCount = 0;
			double nulltime;
			beginMessung(&g_LastCount, &g_FirstCount, &g_Frequency, &nulltime);
			dvk->quickSort(0, dvk->getAnz() - 1,copy);
			endeMessung(g_LastCount, g_FirstCount, g_Frequency, nulltime);
			switch (datei)
			{
			case 1: dvk->inDateiSchreiben("Daten_S.csv",copy);
				break;
			case 2:
				dvk->inDateiSchreiben("Daten1_S.csv",copy);
				break;
			default:
				break;
			}}
			break;

		case 3:{
			GEOKO** copy = dvk->indexCopy();
			LONGLONG g_Frequency = 0, g_FirstCount = 0, g_LastCount = 0;
			double nulltime;
			beginMessung(&g_LastCount, &g_FirstCount, &g_Frequency, &nulltime);
			dvk->SelectionSort(copy);
			endeMessung(g_LastCount, g_FirstCount, g_Frequency, nulltime);
			switch (datei)
			{
				case 1: dvk->inDateiSchreiben("Daten_S.csv", copy);
					break;
				case 2:
					dvk->inDateiSchreiben("Daten1_S.csv", copy);
					break;
				default:
					break;
			}
		}
		break;
		case 4:
			break;
		default:
			cout << "Ungueltige Eingabe";
			break;
		}
	}
	while (choice != 4);

			
	
	
	getchar();
	getchar();

	return 0;
}
