#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "Units.h"

using namespace std;

class Player
{
	int cards[3]; // infantry, cavalry, artillery

	vector<int> provinces_vec;

	bool provice_;

public:
	Player();
	void addProvince(int id);
	void deleteProvince(int province_id);
	int getProvinces(int id) const;
	vector<int>& getProvinces();
};

#endif