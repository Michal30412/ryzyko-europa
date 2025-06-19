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
};

#endif