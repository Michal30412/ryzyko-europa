#include "Button.h"

Button::Button() : Button(0, 0, 0, 0)
{
	;
}

Button::Button(int _x, int _y, int _w, int _h) : GuiComponent(_x, _y, _w, _h)
{
	;
}

Button::Button(int _x, int _y, int _w, int _h, sf::String _text, sf::Font &_font) : Button(_x, _y, _w, _h)
{
	shape.setFillColor(sf::Color::Red);

	text.setFont(_font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);

	setText(_text);
}

void Button::setPosition(int _x, int _y)
{
	GuiComponent::setPosition(_x, _y);

	setText(text.getString());
}

void Button::setRectangle(int _x, int _y, int _w, int _h)
{
	GuiComponent::setRectangle(_x, _y, _w, _h);

	setText(text.getString());
}

void Button::setText(sf::String _text)
{
	text.setString(_text);

	sf::FloatRect r = text.getLocalBounds();
	text.setPosition((float)x + ((float)w - r.width) / 2.f - r.left, (float)y + ((float)h - r.height) / 2.f - r.top);
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