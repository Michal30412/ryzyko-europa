#include "Province.h"

Province::Province()
{
	player_index = -1;

	type = TerrainType::Mountains;

	basic_color = sf::Color::Blue;
	curr_color = sf::Color::Blue;

	units[0] = 1;
	units[1] = 0;
	units[2] = 0;
}

Province::Province(int _index, sf::Font &font, const sf::String &str) : Province()
{
	index = _index;

	text.setFont(font);
	text.setCharacterSize(17);
	text.setFillColor(sf::Color::Black);

	text.setString(str);
}

bool Province::getCapital() const
{
	return capital;
}

int Province::getPlayerIndex() const
{
	return player_index;
}

TerrainType Province::getType() const
{
	return type;
}

Units& Province::getUnits()
{
	return units;
}

void Province::setCapital(bool _capital)
{
	capital = _capital;
}

void Province::setPlayerIndex(int index)
{
	player_index = index;
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
	// cout << text.getPosition().x << ", " << text.getPosition().y << '\n';
}

void Province::setBasicColor(const sf::Color &_color, sf::Image &image, bool change_to_basic)
{
	basic_color = _color;

	if (change_to_basic)
		changeCurrentColor(image, true);
}

void Province::setTempColor(const sf::Color &_color, sf::Image &image, bool change_to_temp)
{
	temp_color = _color;

	if (change_to_temp)
		changeCurrentColor(image, false);
}

void Province::changeCurrentColor(sf::Image &image, bool to_basic)
{
	if (to_basic)
	{
		if (curr_color == basic_color)
			return;
		curr_color = basic_color;
	}
	else
	{
		if (curr_color == temp_color)
			return;
		curr_color = temp_color;
	}

	for (auto& pixel : pixels)
		image.setPixel(pixel.x, pixel.y, curr_color);
}

void Province::print() const
{
	cout << units[0] << ", " << units[1] << ", " << units[2];
}

void Province::draw(sf::RenderWindow &window) const
{
	window.draw(text);
}