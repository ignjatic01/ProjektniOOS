#include "Fifo.h"

Fifo::Fifo() : referenceArr(nullptr), matrica(), brojOkvira(0), brojReferenci(0), pageFaultArr(nullptr)
{
}

Fifo::Fifo(int* arr, int brojOkvira, int brojReferenci) : referenceArr(new int[brojReferenci]), brojOkvira(brojOkvira), brojReferenci(brojReferenci), 
pageFaultArr(new bool[brojReferenci]), matrica(brojOkvira, brojReferenci)
{
	for (int i = 0; i < brojReferenci; i++)
	{
		this->referenceArr[i] = arr[i];
		this->pageFaultArr[i] = true;
	}
	
}

int Fifo::odradiFifoAlgoritam()
{
	int pfNum = 0;
	for (int i = 0; i < this->brojReferenci; i++)
	{
		if (i == 0)
		{
			this->matrica.arr[0] = this->referenceArr[0];
			pfNum++;
		}
		else
		{
			for (int k = 1; k <= this->brojOkvira; k++)
			{
				this->matrica.arr[(k - 1) * this->brojReferenci + i] = this->matrica.arr[(k - 1) * this->brojReferenci + i - 1];
			}
		}
		
		if (!this->fifoProvjera(i, this->referenceArr[i]) && i!=0)
		{
			for (int j = this->brojOkvira-1; j > 0; j--)
			{
				this->matrica.arr[j * this->brojReferenci + i] = this->matrica.arr[(j - 1) * this->brojReferenci + i];
			}
			this->matrica.arr[i] = this->referenceArr[i];
			pfNum++;
		}
		else if(i != 0)
		{
			this->pageFaultArr[i] = false;
		}
	}
	return pfNum;
}

int Fifo::odradiLruAlgoritam()
{
	int pfNum = 0;
	for (int i = 0; i < this->brojReferenci; i++)
	{
		if (i == 0)
		{
			this->matrica.arr[0] = this->referenceArr[0];
			pfNum++;
		}
		else
		{
			for (int k = 1; k <= this->brojOkvira; k++)
			{
				this->matrica.arr[(k - 1) * this->brojReferenci + i] = this->matrica.arr[(k - 1) * this->brojReferenci + i - 1];
			}
			if (this->fifoProvjera(i, this->referenceArr[i]) && i != 0)
			{
				if (this->matrica.arr[(this->brojOkvira - 1) * this->brojReferenci + i] == this->referenceArr[i])
				{
					for (int z = this->brojOkvira - 1; z > 0; z--)
					{
						this->matrica.arr[z * this->brojReferenci + i] = this->matrica.arr[(z - 1) * this->brojReferenci + i];
					}
				}
				else
				{
					int brojac = 0;
					for (int k = 0; k < this->brojOkvira - 1; k++)
					{
						for (int j = k; j < this->brojOkvira; j++)
						{
							if (this->matrica.arr[j * this->brojReferenci + i] == this->referenceArr[i])
							{
								int pom = this->matrica.arr[k * this->brojReferenci + i];
								this->matrica.arr[k * this->brojReferenci + i] = this->matrica.arr[j * this->brojReferenci + i];
								this->matrica.arr[j * this->brojReferenci + i] = pom;
							}
						}
					}
				}
				
				this->matrica.arr[i] = this->referenceArr[i];
			}
			
		}

		if (!this->fifoProvjera(i, this->referenceArr[i]) && i != 0)
		{
			for (int j = this->brojOkvira - 1; j > 0; j--)
			{
				this->matrica.arr[j * this->brojReferenci + i] = this->matrica.arr[(j - 1) * this->brojReferenci + i];
			}
			this->matrica.arr[i] = this->referenceArr[i];
			pfNum++;
		}
		else if (i != 0)
		{
			this->pageFaultArr[i] = false;
		}
	}
	return pfNum;
}

int Fifo::odradiSCAlgoritam()
{
	bool rBitSet = false;
	int rBit;
	std::cout << "Unesite r-bit: ";
	std::cin >> rBit;
	int pfNum = 0;
	for (int i = 0; i < this->brojReferenci; i++)
	{
		if (i == 0)
		{
			this->matrica.arr[0] = this->referenceArr[0];
			if (this->referenceArr[0] == rBit)
			{
				rBitSet = true;
			}
			pfNum++;
		}
		else
		{
			for (int k = 1; k <= this->brojOkvira; k++)
			{
				this->matrica.arr[(k - 1) * this->brojReferenci + i] = this->matrica.arr[(k - 1) * this->brojReferenci + i - 1];
			}
		}

		if (!this->fifoProvjera(i, this->referenceArr[i]) && i != 0)
		{
			if (this->referenceArr[i] == rBit)
			{
				rBitSet = true;
			}
			if (this->matrica.arr[(this->brojOkvira - 1) * this->brojReferenci + i] != rBit)
			{
				for (int j = this->brojOkvira - 1; j > 0; j--)
				{
					this->matrica.arr[j * this->brojReferenci + i] = this->matrica.arr[(j - 1) * this->brojReferenci + i];
				}
				this->matrica.arr[i] = this->referenceArr[i];
				pfNum++;
			}
			else if (rBitSet == false && this->matrica.arr[(this->brojOkvira - 1) * this->brojReferenci + i] == rBit)
			{
				for (int j = this->brojOkvira - 1; j > 0; j--)
				{
					this->matrica.arr[j * this->brojReferenci + i] = this->matrica.arr[(j - 1) * this->brojReferenci + i];
				}
				this->matrica.arr[i] = this->referenceArr[i];
				pfNum++;
			}
			else if (this->matrica.arr[(this->brojOkvira - 1) * this->brojReferenci + i] == rBit && rBitSet == true)
			{
				rBitSet = false;
				int pom = this->matrica.arr[(this->brojOkvira - 1) * this->brojReferenci + i];
				for (int j = 0; j < this->brojOkvira-1; j++)
				{
					this->matrica.arr[(j + 1) * this->brojReferenci + i] = this->matrica.arr[j * this->brojReferenci + i];
				}
				this->matrica.arr[i] = pom;
				for (int j = this->brojOkvira - 1; j > 0; j--)
				{
					this->matrica.arr[j * this->brojReferenci + i] = this->matrica.arr[(j - 1) * this->brojReferenci + i];
				}
				this->matrica.arr[i] = this->referenceArr[i];
				pfNum++;
			}
		}
		else if (i != 0)
		{
			this->pageFaultArr[i] = false;
		}
	}
	return pfNum;
}

int Fifo::odradiLfuAlgoritam()
{
	int pfNum = 0;
	int initialCount;
	int increment;
	int decrement;
	std::cout << "Unesite inicijalnu vrijednost brojaca: ";
	std::cin >> initialCount;
	std::cout << "Unesite inkrement: ";
	std::cin >> increment;
	std::cout << "Unesite dekrement: ";
	std::cin >> decrement;
	Pair* niz = new Pair[this->brojOkvira];
	Pair* niz2 = new Pair[this->brojOkvira + 1];
	for (int i = 0; i < this->brojReferenci; i++)
	{
		if (i == 0)
		{
			this->matrica.arr[0] = this->referenceArr[0];
			niz[0].set(this->referenceArr[0], initialCount);
			pfNum++;
		}
		else if (!this->fifoProvjera(i, this->referenceArr[i]))
		{
			niz2[0].set(this->referenceArr[i], initialCount);
			for (int j = 0; j < this->brojOkvira; j++)
			{
				niz2[j + 1] = niz[j].change(decrement * (-1));
			}
			Fifo::sortPairArr(niz2, this->brojOkvira + 1);
			for (int j = 0; j < this->brojOkvira; j++)
			{
				niz[j] = niz2[j];
				this->matrica.arr[j * this->brojReferenci + i] = niz[j].getPrvi();
			}
			pfNum++;
		}
		else
		{
			for (int k = 0; k < this->brojOkvira; k++)
			{
				if (this->referenceArr[i] == niz[k].getPrvi())
				{
					niz[k] = niz[k].change(increment);
				}
				else
				{
					niz[k] = niz[k].change(decrement * (-1));
				}
			}
			Fifo::sortPairArr(niz, this->brojOkvira);
			for (int j = 0; j < this->brojOkvira; j++)
			{
				this->matrica.arr[j * this->brojReferenci + i] = niz[j].getPrvi();
			}
			this->pageFaultArr[i] = false;
		}
	}
	delete[] niz;
	delete[] niz2;
	return pfNum;
}

int Fifo::odradiOptimalniAlgoritam()
{
	int pfNum = 0;
	for (int i = 0; i < this->brojReferenci; i++)
	{
		if (i == 0)
		{
			this->matrica.arr[0] = this->referenceArr[0];
			pfNum++;
		}
		else if (i<this->brojOkvira)
		{
			for (int j = 0; j < this->brojOkvira-1; j++)
			{
				this->matrica.arr[(j+1) * this->brojReferenci + i] = this->matrica.arr[j  * this->brojReferenci + i - 1];
			}
			this->matrica.arr[i] = this->referenceArr[i];
			pfNum++;
		}
		else if (!this->fifoProvjera(i, this->referenceArr[i]) && i != 0)
		{
			Pair* niz = new Pair[this->brojOkvira];
			for (int k = 0; k < this->brojOkvira; k++)
			{
				niz[k].set(this->matrica.arr[k * this->brojReferenci + i - 1], 0);
			}
			int controlVal = 0;
			for (int j = i; j < this->brojReferenci; j++)
			{
				for (int k = 0; k < this->brojOkvira; k++)
				{
					if (niz[k].getPrvi() == this->referenceArr[j])
					{
						niz[k].setDrugi(1);
						controlVal++;
					}
				}
				if (controlVal == this->brojOkvira - 1)
				{
					break;
				}
			}
			int counter = 0;
			for (int k = 0; k < this->brojOkvira; k++)
			{
				if (niz[k].getDrugi() == 0 && counter == 0)
				{
					niz[k].set(this->referenceArr[i], 0);
					counter++;
				}
				this->matrica.arr[k * this->brojReferenci + i] = niz[k].getPrvi();
			}
			delete[] niz;
			pfNum++;
		}
		else
		{
			for (int k = 1; k <= this->brojOkvira; k++)
			{
				this->matrica.arr[(k - 1) * this->brojReferenci + i] = this->matrica.arr[(k - 1) * this->brojReferenci + i - 1];
			}
			this->pageFaultArr[i] = false;
		}
	}
	return pfNum;
}

bool Fifo::fifoProvjera(int param, int ref)
{
	for (int i = 0; i < this->brojOkvira; i++)
	{
		if (this->matrica.arr[i * this->brojReferenci + param - 1] == ref)
			return true;
	}
	return false;
}

void Fifo::pisi()
{
	for (int i = 0; i < this->brojReferenci; i++)
	{
		std::cout << "  " << this->referenceArr[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < this->brojReferenci; i++)
	{
		if (this->pageFaultArr[i] == true)
		{
			std::cout << " PF";
		}
		else
		{
			std::cout << "   ";
		}
	}
	this->matrica.pisi();
}

void Fifo::sortPairArr(Pair* niz, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (niz[i] < niz[j])
			{
				Pair pom = niz[i];
				niz[i] = niz[j];
				niz[j] = pom;
			}
		}
	}
}

Fifo::~Fifo()
{
	delete[] this->pageFaultArr;
	delete[] this->referenceArr;
}
