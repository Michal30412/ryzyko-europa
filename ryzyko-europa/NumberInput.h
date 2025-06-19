#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "GuiComponent.h"
#include <string>

using namespace std;


class NumberInput : public GuiComponent
{
	int value;
	sf::Text text;

public:
	NumberInput();
	NumberInput(int _x, int _y, int _w, int _h, int _value = 0);
	NumberInput(int _x, int _y, int _w, int _h, int _value, sf::Font &_font);
	void setValue(int _value);
	int getValue() const;
	bool handleEvent(sf::Event &e);
	void draw(sf::RenderWindow &window) const;
};

#endif