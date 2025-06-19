#include "NumberInput.h"

NumberInput::NumberInput() : NumberInput(0, 0, 0, 0)
{
	;
}

NumberInput::NumberInput(int _x, int _y, int _w, int _h, int _value) : GuiComponent(_x, _y, _w, _h)
{
	setValue(_value);
}

NumberInput::NumberInput(int _x, int _y, int _w, int _h, int _value, sf::Font &_font) : NumberInput(_x, _y, _w, _h, _value)
{
	
}

void NumberInput::setValue(int _value)
{
	value = _value;
	text.setString(to_string(_value));
}

int NumberInput::getValue() const
{
	return value;
}

bool NumberInput::handleEvent(sf::Event &e)
{
	if (e.type != sf::Event::MouseButtonPressed)
		return false;

	if (!posIn({ e.mouseButton.x, e.mouseButton.y }))
		return false;

	if (e.mouseButton.button == sf::Mouse::Left)
	{
		++value;
		text.setString(to_string(value));
		return true;
	}
	else if (e.mouseButton.button == sf::Mouse::Right)
	{
		--value;
		text.setString(to_string(value));
		return true;
	}

	return false;
}

void NumberInput::draw(sf::RenderWindow &window) const
{
	window.draw(shape);
}