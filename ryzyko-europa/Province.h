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
	City
};

class Province
{
	friend class Map;

	int index;

	ProvinceType type;
	Units units;

	vector<int> neighbours;
	vector<sf::Vector2f> pixels;
	sf::Vector2<double> center;
	sf::Color color;

	sf::Text text;

public:
	Province();
	Province(int _index, sf::Font &font, const sf::String &str = "");
	void setString(const sf::String &str);
	void setCenter(const sf::Vector2<double>& _center);
	void setColor(const sf::Color &_color, sf::Image &image);
	void print() const;
	void draw(sf::RenderWindow &window) const;
};

#endif