#include "Button.h"

Button::Button() : Button(0, 0, 0, 0, "")
{
	;
}

Button::Button(int _x, int _y, int _w, int _h) : Button(_x, _y, _w, _h, "")
{
	;
}

Button::Button(int _x, int _y, int _w, int _h, sf::String _text) : GuiComponent(_x, _y, _w, _h)
{
	shape.setFillColor(sf::Color::Red);

	text.setPosition(x + 10, y + 10);
	text.setString(_text);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
}

Button::Button(int _x, int _y, int _w, int _h, sf::String _text, sf::Font &_font) : Button(_x, _y, _w, _h, _text)
{
	text.setFont(_font);
}

void Button::setPosition(int _x, int _y)
{
	GuiComponent::setPosition(_x, _y);
	
	text.setPosition(x + 10, y + 10);
}

void Button::setRectangle(int _x, int _y, int _w, int _h)
{
	GuiComponent::setRectangle(_x, _y, _w, _h);

	text.setPosition(x + 10, y + 10);
}

void Button::setText(sf::String _text)
{
	text.setString(_text);
}

bool Button::handleEvent(sf::Event &e)
{
	if (e.type != sf::Event::MouseButtonPressed)
		return false;

	if (e.mouseButton.button != sf::Mouse::Left)
		return false;

	return posIn({ e.mouseButton.x, e.mouseButton.y });
}

void Button::draw(sf::RenderWindow &window) const
{
	window.draw(shape);
	window.draw(text);
}