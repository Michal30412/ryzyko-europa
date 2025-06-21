#include "Player.h"

Player::Player(int id, const sf::Color& _color) : cards(3, 2, 1)
{
	player_id = id;

	color = _color;

	province_captured = false;
}

void Player::setColor(sf::Color &_color)
{
	color = _color;
}

void Player::startTurn()
{
	if (province_captured)
	{
		int unit_type = 1 + rand() % 2; // Cavalry or Artillery
		++cards[unit_type];

		province_captured = false;
	}
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

sf::Color& Player::getColor()
{
	return color;
}

int Player::getProvince(int id) const
{
	return provinces_vec[id];
}

vector<int>& Player::getProvincesVec()
{
	return provinces_vec;
}

Units& Player::getCards()
{
	return cards;
}

void Player::printCards() const
{
	cout << "Player " << player_id << " cards:\n";
	cout << "Infantry:\t" << cards[UnitType::Infantry] << '\n';
	cout << "Cavalry:\t" << cards[UnitType::Cavalry] << '\n';
	cout << "Artillery:\t" << cards[UnitType::Artillery] << '\n';
}