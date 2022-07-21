#pragma once

class Pair
{
private:
	int prvi;
	int drugi;
public:
	Pair();
	Pair(int prvi, int drugi);
	void set(int prvi, int drugi);
	void setDrugi(int value);
	int getDrugi();
	int getPrvi();
	Pair change(int value);
	bool operator<(Pair drugi) const;
	bool operator>(Pair drugi) const;
};

