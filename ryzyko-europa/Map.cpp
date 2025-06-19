#include "Map.h"

Map::Map()
{
	image.loadFromFile("img3.png");

	texture.loadFromImage(image);
	sf::Vector2f size = sf::Vector2f(texture.getSize());

	rectangle.setSize(size);
	rectangle.setPosition((1280.f - size.x) / 2.f, (720.f - size.y) / 2.f);
	rectangle.setTexture(&texture);

	active_province_id = -1;
	show_neighbours = false;
}

void Map::init(sf::Font &font)
{
	analyzeImage(font);

	updateProvinces();

	provinces_vec[0].neighbours.assign({
		&provinces_vec[1],
		&provinces_vec[2]
		});

	provinces_vec[1].neighbours.assign({
		&provinces_vec[0],
		&provinces_vec[2],
		&provinces_vec[6],
		&provinces_vec[12]
		});

	provinces_vec[2].neighbours.assign({
		&provinces_vec[0],
		&provinces_vec[3],
		&provinces_vec[4]
		});

	provinces_vec[3].neighbours.assign({
		&provinces_vec[1],
		&provinces_vec[2],
		&provinces_vec[4]
		});

	provinces_vec[4].neighbours.assign({
		&provinces_vec[2],
		&provinces_vec[3]
		});
}

int Map::getProvinceId(int x, int y) const
{
	x -= rectangle.getPosition().x;
	y -= rectangle.getPosition().y;

	if (x < 0 || image.getSize().x <= x || y < 0 || image.getSize().y <= y)
		return -1;

	return index_vec[x][y];
}

void Map::analyzeImage(sf::Font &font)
{
	map<tuple<sf::Uint8, sf::Uint8, sf::Uint8>, int> colors_map;

	int w = texture.getSize().x;
	int h = texture.getSize().y;

	index_vec.assign(w, vector<int>(h, -1));

	int new_index = 0;
	for (int x = 0; x < w; ++x)
	{
		for (int y = 0; y < h; ++y)
		{
			sf::Color color = image.getPixel(x, y);

			if (color == sf::Color::White || color == sf::Color::Black)
				continue;

			tuple<sf::Uint8, sf::Uint8, sf::Uint8> tp = { color.r, color.g, color.b };

			auto element = colors_map.find(tp);
			if (element == colors_map.end())
			{
				colors_map.emplace(tp, new_index);
				index_vec[x][y] = new_index;

				Province province = Province(font, to_string(new_index));
				province.pixels.emplace_back(x, y);
				province.center = sf::Vector2<double>(x, y);

				provinces_vec.push_back(province);

				++new_index;
			}
			else
			{
				index_vec[x][y] = element->second;
				Province &province = provinces_vec[element->second];
				province.pixels.emplace_back(x, y);
				province.center += sf::Vector2<double>(x, y);
			}

			image.setPixel(x, y, sf::Color::Blue);
		}
	}

	texture.loadFromImage(image);
}

void Map::updateProvinces()
{
	cout << "Count of provinces: " << provinces_vec.size() << '\n';

	for (auto& province : provinces_vec)
	{
		sf::Vector2<double> new_center = province.center / (double)province.pixels.size() + (sf::Vector2<double>)rectangle.getPosition();
		province.setCenter(new_center);
	}
}

void printColor(sf::Color &color)
{
	cout << "( " << (int)color.r << ", " << (int)color.g << ", " << (int)color.r << " )";
}

void Map::setProvinceColor(int id, const sf::Color &color)
{
	if (id == -1)
		return;

	for (auto pos : provinces_vec[id].pixels)
		image.setPixel(pos.x, pos.y, color);
}

void Map::setProvinceColor(Province& province, const sf::Color &color)
{
	for (auto pos : province.pixels)
		image.setPixel(pos.x, pos.y, color);
}

int Map::updateActiveProvince(int x, int y, bool with_neighbours)
{
	x -= rectangle.getPosition().x;
	y -= rectangle.getPosition().y;

	if (x < 0 || image.getSize().x <= x || y < 0 || image.getSize().y <= y)
		return -1;

	int next_province_id = -1;
	if (active_province_id != index_vec[x][y])
		next_province_id = index_vec[x][y];

	if (active_province_id != -1)
	{
		setProvinceColor(active_province_id, sf::Color::Blue);
		if (show_neighbours)
		{
			for (auto* neighbour : provinces_vec[active_province_id].neighbours)
				setProvinceColor(*neighbour, sf::Color::Blue);
		}
	}

	if (next_province_id != -1)
	{
		setProvinceColor(next_province_id, sf::Color::Red);
		if (with_neighbours)
		{
			for (auto* neighbour : provinces_vec[next_province_id].neighbours)
				setProvinceColor(*neighbour, sf::Color::Yellow);
		}
	}

	texture.loadFromImage(image);

	active_province_id = next_province_id;
	show_neighbours = with_neighbours;
	
	return active_province_id;
}

void Map::draw(sf::RenderWindow &window) const
{
	window.draw(rectangle);

	//*
	for (auto& province : provinces_vec)
	{
		province.draw(window);
	}
	//*/

	/*
	if (0 <= active_province_id)
	{
		provinces_vec[active_province_id].draw(window, sf::Color(0, 255, 0, 63));

		for (auto* neighbour : provinces_vec[active_province_id].neighbours)
		{
			neighbour->draw(window, sf::Color(255, 0, 0, 63));
		}
	}
	//*/
}