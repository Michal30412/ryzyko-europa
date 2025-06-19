#ifndef PROVINCE_H
#define PROVINCE_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Rect
{
	int x1;
	int y1;
	int x2;
	int y2;

	Rect()
	{
		x1 = 0;
		y1 = 0;
		x2 = 0;
		y2 = 0;
	}
	Rect(int _x1, int _y1, int _x2, int _y2)
	{
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	}
	void move(int x, int y)
	{
		x1 += x;
		y1 += y;
		x2 += x;
		y2 += y;
	}
	void merge(const Rect &r)
	{
		x1 = min(x1, r.x1);
		y1 = min(y1, r.y1);
		x2 = max(x2, r.x2);
		y2 = max(y2, r.y2);
	}
	bool posIn(const sf::Vector2i pos) const
	{
		return x1 <= pos.x && pos.x <= x2 && y1 <= pos.y && pos.y <= y2;
	}
	void print() const
	{
		cout << x1 << ", " << y1 << ", " << x2 << ", " << y2;
	}
};

class Province
{
	friend class Map;

	Rect rect;

	string name;

	sf::Text text;

	vector<Province*> neighbours;

	vector<sf::Vector2f> pixels;

	// sf::Texture texture;
	// sf::RectangleShape rectangle;

public:
	Province();
	Province(const Rect &_rect);
	void draw(sf::RenderWindow &window, const sf::Color &color) const;
};

#endif