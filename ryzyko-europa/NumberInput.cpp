#include "NumberInput.h"

NumberInput::NumberInput() : NumberInput(0, 0, 0, 0)
{
	;
}

NumberInput::NumberInput(int _x, int _y, int _w, int _h, int _value) : GuiComponent(_x, _y, _w, _h)
{
	shape.setFillColor(sf::Color::Red);

	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);

	setValue(_value);
	prv_value = 0;
}

NumberInput::NumberInput(int _x, int _y, int _w, int _h, int _value, sf::Font &_font) : GuiComponent(_x, _y, _w, _h)
{
	shape.setFillColor(sf::Color::Red);

	text.setFont(_font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);

	setValue(_value);
	prv_value = 0;
}

void NumberInput::setValue(int _value)
{
	prv_value = value;
	value = _value;
	text.setString(to_string(_value));

	sf::FloatRect r = text.getLocalBounds();
	text.setPosition((float)x + ((float)w - r.width) / 2.f - r.left, (float)y + ((float)h - r.height) / 2.f - r.top);
}

int NumberInput::getPrvValue() const
{
	return prv_value;
}

int NumberInput::getValue() const
{
	return value;
}

int NumberInput::getDifference() const
{
	return value - prv_value;
}

bool NumberInput::handleEvent(sf::Event &e)
{
	if (e.type != sf::Event::MouseButtonPressed)
		return false;

	if (!posIn({ e.mouseButton.x, e.mouseButton.y }))
		return false;

	if (e.mouseButton.button == sf::Mouse::Left)
	{
		setValue(value + 1);
		return true;
	}
	else if (e.mouseButton.button == sf::Mouse::Right)
	{
		setValue(value - 1);
		return true;
	}

	return false;
}

void NumberInput::draw(sf::RenderWindow &window) const
{
	window.draw(shape);
	window.draw(text);
}