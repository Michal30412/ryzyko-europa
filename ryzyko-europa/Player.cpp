#include "Player.h"

Player::Player()
{
	cards[UnitType::Infantry] = 3;
	cards[UnitType::Cavalry] = 2;
	cards[UnitType::Artillery] = 1;
}

void Player::addProvince(int id)
{
	provinces_vec.push_back(id);
}

void Player::deleteProvince(int province_id)
{
	int id = 0;
	while (id < provinces_vec.size())
	{
		if (provinces_vec.at(id) == province_id)
			break;
		++id;
	}

	if (id >= provinces_vec.size())
		return;

	provinces_vec[id] = provinces_vec.back();
	provinces_vec.pop_back();
}

int Player::getProvinces(int id) const
{
	return provinces_vec[id];
}

vector<int>& Player::getProvinces()
{
	return provinces_vec;
}