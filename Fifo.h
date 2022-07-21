#pragma once
#include <iostream>
#include "Matrix.h"
#include "Pair.h"

class Fifo
{
private:
	Matrix matrica;
	int* referenceArr;
	int brojOkvira;
	int brojReferenci;
	bool* pageFaultArr;
public:
	Fifo();
	Fifo(int* arr, int brojOkvira, int brojReferenci);
	int odradiFifoAlgoritam();
	int odradiLruAlgoritam();
	int odradiSCAlgoritam();
	int odradiLfuAlgoritam();
	int odradiOptimalniAlgoritam();
	bool fifoProvjera(int param, int ref);
	void pisi();
	static void sortPairArr(Pair* niz, int n);
	~Fifo();
};
