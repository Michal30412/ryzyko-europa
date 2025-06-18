#ifndef MAP_H
#define MAP_H

#include "Province.h"
#include <map>

using namespace std;

class Map
{
	sf::Image image;
	sf::Texture texture;
	sf::RectangleShape rectangle;

	vector<Province> provinces_vec;
	vector<vector<int>> index_vec;

	int active_province_id;

public:
	Map();
	void init();
	void analyzeImage();
	int updateProvinceId(int x, int y);
	void draw(sf::RenderWindow &window) const;
};

#endif