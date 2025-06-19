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
	bool show_neighbours;

public:
	Map();
	void init(sf::Font &font);
	int getProvinceId(int x, int y) const;
	void analyzeImage(sf::Font &font);
	void updateProvinces();
	void loadNeighbours(string path);
	void setProvinceColor(int id, const sf::Color &color);
	void setProvinceColor(Province& province, const sf::Color &color);
	int updateActiveProvince(int x, int y, bool with_neighbours = false);
	void draw(sf::RenderWindow &window) const;
};

#endif