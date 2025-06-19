#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include <SFML/Graphics.hpp>

class GuiComponent
{
protected:
	int x;
	int y;
	int w;
	int h;
	sf::RectangleShape shape;

public:
	GuiComponent();
	GuiComponent(int _x, int _y, int _w, int _h);
	bool posIn(const sf::Vector2i &pos);
	virtual void setPosition(int _x, int _y);
	virtual void setRectangle(int _x, int _y, int _w, int _h);
	virtual bool handleEvent(sf::Event &e) = 0;
	virtual void draw(sf::RenderWindow &window) const = 0;
};

#endif