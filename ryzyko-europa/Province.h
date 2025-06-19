#ifndef PROVINCE_H
#define PROVINCE_H

#include <string>
#include <vector>

#include "Units.h"
#include "Rect.h"

enum class ProvinceType
{
	Mountain,
	Forest,
	Field,
	City,
	Capital
};

class Province
{
	friend class Map;

	ProvinceType type;
	Units units;

	vector<Province*> neighbours;
	vector<sf::Vector2f> pixels;
	sf::Vector2<double> center;

	sf::Text text;

public:
	Province();
	Province(sf::Font &font, const sf::String &str = "");
	void setString(const sf::String &str);
	void setCenter(sf::Vector2<double>& _center);
	void print() const;
	void draw(sf::RenderWindow &window) const;
};

#endif