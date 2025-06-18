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

void Province::draw(sf::RenderWindow &window) const
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(rect.x2 - rect.x1, rect.y2 - rect.y1));
	rectangle.setPosition(rect.x1, rect.y1);
	// rectangle.setFillColor(sf::Color::Green);
	rectangle.setFillColor(sf::Color(0, 255, 0, 63));
	window.draw(rectangle);
}