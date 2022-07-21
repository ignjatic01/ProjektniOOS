#include "Pair.h"

Pair::Pair() : prvi(0), drugi(0)
{
}

Pair::Pair(int prvi, int drugi) : prvi(prvi), drugi(drugi)
{
}

void Pair::set(int prvi, int drugi)
{
	this->prvi = prvi;
	this->drugi = drugi;
}

void Pair::setDrugi(int value)
{
	this->drugi = value;
}

int Pair::getDrugi()
{
	return this->drugi;
}

int Pair::getPrvi()
{
	return this->prvi;
}

Pair Pair::change(int value)
{
	return Pair(this->prvi, this->drugi + value);
}

bool Pair::operator<(Pair drugi) const
{
	if (this->drugi < drugi.drugi)
		return true;
	else return false;
}

bool Pair::operator>(Pair drugi) const
{
	if (this->drugi > drugi.drugi)
		return true;
	else return false;
}

