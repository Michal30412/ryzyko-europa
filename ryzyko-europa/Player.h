#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Units.h"

using namespace std;

class Player
{
	int player_id;

	Units cards;
	vector<int> provinces_vec;
	sf::Color color;

	bool province_captured;

public:
	Player(int id, const sf::Color& _color);
	void setColor(sf::Color &_color);
	void startTurn();
	void addProvince(int id);
	void deleteProvince(int province_id);
	sf::Color& getColor();
	int getProvince(int id) const;
	vector<int>& getProvincesVec();
	Units& getCards();
	void printCards() const;
};

#endif