#include "DVKE.h"



DVKE::DVKE() :v(nullptr), n(nullptr)
{
}


DVKE::~DVKE()
{
}

DVKE* DVKE::getN() {
	return n;
}

DVKE* DVKE::getV() {
	return v;
}
void DVKE::setN(DVKE* obj){
	this->n = obj;
}
void DVKE::setV(DVKE* obj) {
	this->v = obj;
}