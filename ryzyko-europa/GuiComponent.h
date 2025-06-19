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

	sf::Text text;

public:
	GuiComponent();
	GuiComponent(int _x, int _y, int _w, int _h);
	GuiComponent(int _x, int _y, int _w, int _h, const sf::Font &font);
	bool posIn(const sf::Vector2i &pos);
	void setFont(const sf::Font &font);
	virtual void setPosition(int _x, int _y);
	virtual void setRectangle(int _x, int _y, int _w, int _h);
	virtual bool handleEvent(sf::Event &e) = 0;
	virtual void draw(sf::RenderWindow &window) const = 0;
};

#endif