#include <iostream>
#include "Matrix.h"
#include "Fifo.h"

int duzina(char* s);

int main()
{
    std::cout << "Dobar dan i dobro dosli!"<<std::endl;
    std::cout << "Unesite broj okvira: ";
    int brojOkvira;
    std::cin >> brojOkvira;
    std::cout << "Unesite broj referenci: ";
    int brojReferenci;
    std::cin >> brojReferenci;
    int* niz = new int[brojReferenci];
    for (int i = 0; i < brojReferenci; i++)
    {
        std::cout << "Unos " << i + 1 << ": ";
        std::cin >> niz[i];
    }
    std::cout << "Izaberite algoritam: FIFO[0]; LRU[1]; Second Chance[2]; LFU[3]; Optimalni algoritam[4]" << std::endl;
    int param;
    std::cin >> param;
    static int pfNum;
    switch (param)
    {
    case 0:
    {
        Fifo test(niz, brojOkvira, brojReferenci);
        pfNum = test.odradiFifoAlgoritam();
        test.pisi();
        std::cout << std::endl;
        break;
    }
    case 1:
    {
        Fifo test(niz, brojOkvira, brojReferenci);
        pfNum = test.odradiLruAlgoritam();
        test.pisi();
        std::cout << std::endl;
        break;
    }
    case 2:
    {
        Fifo test(niz, brojOkvira, brojReferenci);
        pfNum = test.odradiSCAlgoritam();
        test.pisi();
        std::cout << std::endl;
        break;
    }
    case 3:
    {
        Fifo test(niz, brojOkvira, brojReferenci);
        pfNum = test.odradiLfuAlgoritam();
        test.pisi();
        std::cout << std::endl;
        break;
    }
    case 4:
    {
        Fifo test(niz, brojOkvira, brojReferenci);
        pfNum = test.odradiOptimalniAlgoritam();
        test.pisi();
        std::cout << std::endl;
        break;
    }
    }
    double procenat = (double)pfNum / (double)brojReferenci;
    std::cout << "Efikasnost algoritma: PF = " << pfNum << "           pf = " << procenat * 100 << "%";
    delete[] niz;
}

