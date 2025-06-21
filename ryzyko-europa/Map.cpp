#include "Map.h"
#include <map>

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

	provinces_vec[0].neighbours.assign({ 1, 2, 37 });
	provinces_vec[1].neighbours.assign({ 0, 2, 6, 12 });
	provinces_vec[2].neighbours.assign({ 0, 1, 3, 6 });
	provinces_vec[3].neighbours.assign({ 2, 6, 5, 4 });
	provinces_vec[4].neighbours.assign({ 3, 5, 8 });
	provinces_vec[5].neighbours.assign({ 3, 6, 11, 4 });
	provinces_vec[6].neighbours.assign({ 2, 1, 11, 5, 3 });
	provinces_vec[7].neighbours.assign({ 8, 9, 10 });
	provinces_vec[8].neighbours.assign({ 4, 9, 7 });
	provinces_vec[9].neighbours.assign({ 8, 7, 10, 16 });
	provinces_vec[10].neighbours.assign({ 7, 9 });
	provinces_vec[11].neighbours.assign({ 5, 6, 12 });
	provinces_vec[12].neighbours.assign({ 1, 11, 15 });
	provinces_vec[13].neighbours.assign({ 15, 18, 17, 14 });
	provinces_vec[14].neighbours.assign({ 13, 17, 19, 16 });
	provinces_vec[15].neighbours.assign({ 12, 18, 13 });
	provinces_vec[16].neighbours.assign({ 9, 14, 19, 21, 25, 20 });
	provinces_vec[17].neighbours.assign({ 14, 19, 23, 18, 13 });
	provinces_vec[18].neighbours.assign({ 15, 13, 17, 23 });
	provinces_vec[19].neighbours.assign({ 14, 17, 23, 24, 21, 16 });
	provinces_vec[20].neighbours.assign({ 16, 25, 22 });
	provinces_vec[21].neighbours.assign({ 16, 25, 24, 19 });
	provinces_vec[22].neighbours.assign({ 20, 25, 26 });
	provinces_vec[23].neighbours.assign({ 18, 17, 19, 24, 27, 28 });
	provinces_vec[24].neighbours.assign({ 19, 21, 29, 27, 23, 25 });
	provinces_vec[25].neighbours.assign({ 16, 20, 22, 21, 24 });
	provinces_vec[26].neighbours.assign({ 22 });
	provinces_vec[27].neighbours.assign({ 23, 24, 29, 31, 28 });
	provinces_vec[28].neighbours.assign({ 23, 27, 31, 30 });
	provinces_vec[29].neighbours.assign({ 24, 27, 31, 36});
	provinces_vec[30].neighbours.assign({ 28, 31, 33, 32, 35 });
	provinces_vec[31].neighbours.assign({ 28, 27, 29, 36, 33, 30 });
	provinces_vec[32].neighbours.assign({ 37, 35, 30, 33 });
	provinces_vec[33].neighbours.assign({ 37, 32, 30, 31, 40 });
	provinces_vec[34].neighbours.assign({ 36, 39, 38 });
	provinces_vec[35].neighbours.assign({ 30, 32, 37 });
	provinces_vec[36].neighbours.assign({ 31, 29, 34 });
	provinces_vec[37].neighbours.assign({ 0, 35, 32, 33, 40 });
	provinces_vec[38].neighbours.assign({ 34, 41 });
	provinces_vec[39].neighbours.assign({ 34, 41 });
	provinces_vec[40].neighbours.assign({ 33, 37 });
	provinces_vec[41].neighbours.assign({ 38, 39 });

	provinces_vec[0].type = TerrainType::Mountains;
	provinces_vec[1].type = TerrainType::Plains;
	provinces_vec[2].type = TerrainType::Plains;
	provinces_vec[3].type = TerrainType::Mountains;
	provinces_vec[4].type = TerrainType::Forest;
	provinces_vec[5].type = TerrainType::City;
	provinces_vec[6].type = TerrainType::City;
	provinces_vec[7].type = TerrainType::Mountains;
	provinces_vec[8].type = TerrainType::Forest;
	provinces_vec[9].type = TerrainType::Forest;
	provinces_vec[10].type = TerrainType::Mountains;
	provinces_vec[11].type = TerrainType::City;
	provinces_vec[12].type = TerrainType::Plains;
	provinces_vec[13].type = TerrainType::City;
	provinces_vec[14].type = TerrainType::City;
	provinces_vec[15].type = TerrainType::Plains;
	provinces_vec[16].type = TerrainType::Plains;
	provinces_vec[17].type = TerrainType::City;
	provinces_vec[18].type = TerrainType::Plains;
	provinces_vec[19].type = TerrainType::Mountains;
	provinces_vec[20].type = TerrainType::Forest;
	provinces_vec[21].type = TerrainType::Plains;
	provinces_vec[22].type = TerrainType::Mountains;
	provinces_vec[23].type = TerrainType::Plains;
	provinces_vec[24].type = TerrainType::Plains;
	provinces_vec[25].type = TerrainType::Forest;
	provinces_vec[26].type = TerrainType::Forest;
	provinces_vec[27].type = TerrainType::Mountains;
	provinces_vec[28].type = TerrainType::Plains;
	provinces_vec[29].type = TerrainType::Forest;
	provinces_vec[30].type = TerrainType::Forest;
	provinces_vec[31].type = TerrainType::City;
	provinces_vec[32].type = TerrainType::Plains;
	provinces_vec[33].type = TerrainType::City;
	provinces_vec[34].type = TerrainType::Forest;
	provinces_vec[35].type = TerrainType::Plains;
	provinces_vec[36].type = TerrainType::Forest;
	provinces_vec[37].type = TerrainType::Plains;
	provinces_vec[38].type = TerrainType::Plains;
	provinces_vec[39].type = TerrainType::Forest;
	provinces_vec[40].type = TerrainType::City;
	provinces_vec[41].type = TerrainType::Mountains;

	provinces_vec[0].setString("Alaska");
	provinces_vec[1].setString("Nw.Territory");
	provinces_vec[2].setString("Alberta");
	provinces_vec[3].setString("W.USA");
	provinces_vec[4].setString("Mexico");
	provinces_vec[5].setString("E.USA");
	provinces_vec[6].setString("Ontario");
	provinces_vec[7].setString("Peru");
	provinces_vec[8].setString("Colombia");
	provinces_vec[9].setString("Brazil");
	provinces_vec[10].setString("Argentina");
	provinces_vec[11].setString("Quebec");
	provinces_vec[12].setString("Greenland");
	provinces_vec[13].setString("UK");
	provinces_vec[14].setString("W.Europe");
	provinces_vec[15].setString("Iceland");
	provinces_vec[16].setString("Sahara");
	provinces_vec[17].setString("C.Europe");
	provinces_vec[18].setString("Scandinavia");
	provinces_vec[19].setString("S.Europe");
	provinces_vec[20].setString("Kongo");
	provinces_vec[21].setString("Egypt");
	provinces_vec[22].setString("S.Africa");
	provinces_vec[23].setString("E.Europe");
	provinces_vec[24].setString("M.East");
	provinces_vec[25].setString("Ethiopia");
	provinces_vec[26].setString("Madagascar");
	provinces_vec[27].setString("Afghanistan");
	provinces_vec[28].setString("Ural");
	provinces_vec[29].setString("India");
	provinces_vec[30].setString("Siberia");
	provinces_vec[31].setString("China");
	provinces_vec[32].setString("Irkutsk");
	provinces_vec[33].setString("Korea");
	provinces_vec[34].setString("Indonesia");
	provinces_vec[35].setString("Yakutsk");
	provinces_vec[36].setString("Thailand");
	provinces_vec[37].setString("Kamchatka");
	provinces_vec[38].setString("W.Australia");
	provinces_vec[39].setString("N.Guinea");
	provinces_vec[40].setString("Japan");
	provinces_vec[41].setString("E.Australia");
}

int Map::getProvinceId(int x, int y) const
{
	x -= rectangle.getPosition().x;
	y -= rectangle.getPosition().y;

	if (x < 0 || image.getSize().x <= x || y < 0 || image.getSize().y <= y)
		return -1;

	return index_vec[x][y];
}

Province& Map::getActiveProvince()
{
	return provinces_vec[active_province_id];
}

int Map::getActiveProvinceId() const
{
	return active_province_id;
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

				Province province = Province(new_index, font, to_string(new_index));
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

/*
void Map::setProvinceColor(int id, const sf::Color &color)
{
	if (id == -1)
		return;

	provinces_vec[id].setColor(color, image);
}

void Map::setProvinceColor(Province& province, const sf::Color &color)
{
	province.setColor(color, image);
}
*/

void Map::setActiveProvince(int id, bool with_neighbours)
{
	if (active_province_id != -1)
	{
		provinces_vec[active_province_id].changeCurrentColor(image, true);
		if (show_neighbours)
		{
			for (auto neighbour : provinces_vec[active_province_id].neighbours)
				provinces_vec[neighbour].changeCurrentColor(image, true);
		}
	}

	if (id != -1)
	{
		provinces_vec[id].setTempColor(sf::Color::Red, image);
		if (with_neighbours)
		{
			for (auto neighbour : provinces_vec[id].neighbours)
				provinces_vec[neighbour].setTempColor(sf::Color::Yellow, image);
		}
	}

	texture.loadFromImage(image);

	active_province_id = id;
	show_neighbours = with_neighbours;
}

int Map::updateActiveProvince(int x, int y, bool with_neighbours)
{
	x -= rectangle.getPosition().x;
	y -= rectangle.getPosition().y;

	if (x < 0 || image.getSize().x <= x || y < 0 || image.getSize().y <= y)
		return -1;

	int next_id = index_vec[x][y];
	if (next_id == active_province_id)
		next_id = -1;

	setActiveProvince(next_id, with_neighbours);
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