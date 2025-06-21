#ifndef PROVINCE_H
#define PROVINCE_H

#include <string>
#include <vector>

#include "Units.h"
#include "Rect.h"

enum class TerrainType
{
	Mountains,
	Forest,
	Plains,
	City
};

class Province
{
	friend class Map;

	bool capital;
	int index;
	int player_index;

	TerrainType type;
	Units units;

	vector<int> neighbours;
	vector<sf::Vector2f> pixels;
	sf::Vector2<double> center;

	sf::Color basic_color;
	sf::Color temp_color;
	sf::Color curr_color;

	sf::Text text;

public:
	Province();
	Province(int _index, sf::Font &font, const sf::String &str = "");
	bool getCapital() const;
	int getPlayerIndex() const;
	TerrainType getType() const;
	Units& getUnits();
	void setCapital(bool _capital);
	void setPlayerIndex(int index);
	void setString(const sf::String &str);
	void setCenter(const sf::Vector2<double>& _center);
	void setBasicColor(const sf::Color &_color, sf::Image &image, bool change_to_basic = true);
	void setTempColor(const sf::Color &_color, sf::Image &image, bool change_to_temp = true);
	void changeCurrentColor(sf::Image &image, bool to_basic);
	void print() const;
	void draw(sf::RenderWindow &window) const;
};

#endif