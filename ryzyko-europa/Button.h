#ifndef BUTTON_H
#define BUTTON_H

#include "GuiComponent.h"

class Button : public GuiComponent
{
public:
	Button();
	Button(int _x, int _y, int _w, int _h);
	Button(int _x, int _y, int _w, int _h, sf::String _text);
	Button(int _x, int _y, int _w, int _h, sf::String _text, sf::Font &_font);
	void setPosition(int _x, int _y);
	void setRectangle(int _x, int _y, int _w, int _h);
	void setText(sf::String text);
	bool handleEvent(sf::Event &e); // returns true if clicked
	void draw(sf::RenderWindow &window) const;
};

#endif