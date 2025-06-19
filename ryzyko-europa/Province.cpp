#include "Province.h"

Province::Province()
{
	type = ProvinceType::Mountain;
}

Province::Province(int _index, sf::Font &font, const sf::String &str) : Province()
{
	index = _index;

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);

	text.setString(str);
}

void Province::setString(const sf::String &str)
{
	text.setString(str);
	setCenter(center);
}

void Province::setCenter(const sf::Vector2<double>& _center)
{
	center = _center;
	sf::FloatRect rect = text.getLocalBounds();

	text.setPosition(center.x - rect.width / 2.f - rect.left, center.y - rect.height / 2.f - rect.top);
	cout << text.getPosition().x << ", " << text.getPosition().y << '\n';
}

void Province::setColor(const sf::Color &_color, sf::Image &image)
{
	if (color == _color)
		return;

	color = _color;
	for (auto& pixel : pixels)
	{
		image.setPixel(pixel.x, pixel.y, color);
	}
}

void Province::print() const
{
	cout << units.count_tab[0] << ", " << units.count_tab[1] << ", " << units.count_tab[2];
}

void Province::draw(sf::RenderWindow &window) const
{
	window.draw(text);
}