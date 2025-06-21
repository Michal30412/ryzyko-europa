#ifndef UNITS_H
#define UNITS_H

enum UnitType
{
	Infantry,
	Cavalry,
	Artillery
};

struct Units
{
	int count_tab[3];

	Units() : Units(1, 0, 0)
	{
		;
	}
	Units(int infantry, int cavalry, int artillery)
	{
		count_tab[UnitType::Infantry] = infantry;
		count_tab[UnitType::Cavalry] = cavalry;
		count_tab[UnitType::Artillery] = artillery;
	}
	int& operator[](int index)
	{
		return count_tab[index];
	}
	const int& operator[](int index) const
	{
		return count_tab[index];
	}
	/*
	void operator-=(const Units &right)
	{
		count_tab[0] -= right.count_tab[0];
		count_tab[1] -= right.count_tab[1];
		count_tab[2] -= right.count_tab[2];
	}
	void operator+=(const Units &right)
	{
		count_tab[0] += right.count_tab[0];
		count_tab[1] += right.count_tab[1];
		count_tab[2] += right.count_tab[2];
	}
	*/
};

#endif