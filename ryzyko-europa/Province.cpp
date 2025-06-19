#include "Province.h"

Province::Province()
{
	// cout << "smth\n";

	// text.setPosition()
}

Province::Province(const Rect &_rect)
{
	rect = _rect;
}

void Province::draw(sf::RenderWindow &window, const sf::Color &color) const
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(rect.x2 - rect.x1 + 1, rect.y2 - rect.y1 + 1));
	rectangle.setPosition(rect.x1, rect.y1);
	// rectangle.setFillColor(sf::Color::Green);
	rectangle.setFillColor(color);
	window.draw(rectangle);
}