#pragma once
class DVKE
{

private:
	DVKE* v;
	DVKE* n;

public:
	DVKE();
	~DVKE();
	DVKE* getV();
	DVKE* getN();
	void setV(DVKE* obj);
	void setN(DVKE* obj);
};

