#include "Map.h"

Map::Map()
{
	// cout << "smth\n";

	image.loadFromFile("img.png");

	texture.loadFromImage(image);
	sf::Vector2f size = sf::Vector2f(texture.getSize());

	rectangle.setSize(size);
	rectangle.setPosition((1280.f - size.x) / 2.f, (720.f - size.y) / 2.f);
	rectangle.setTexture(&texture);

	active_province_id = -1;
}

void Map::init()
{
	provinces_vec.assign(5, Province());

	provinces_vec.at(0).neighbours.assign({
		&provinces_vec.at(1),
		&provinces_vec.at(3)
		});

	provinces_vec.at(1).neighbours.assign({
		&provinces_vec.at(0),
		&provinces_vec.at(2),
		&provinces_vec.at(4)
		});

	provinces_vec.at(2).neighbours.assign({
		&provinces_vec.at(1),
		&provinces_vec.at(4)
		});

	provinces_vec.at(3).neighbours.assign({
		&provinces_vec.at(0),
		&provinces_vec.at(4)
		});

	provinces_vec.at(4).neighbours.assign({
		&provinces_vec.at(1),
		&provinces_vec.at(2),
		&provinces_vec.at(3)
		});
}

void Map::analyzeImage()
{
	int w = texture.getSize().x;
	int h = texture.getSize().y;

	index_vec.assign(w, vector<int>(h, -1));

	int index = 0;
	for (int x = 0; x < w; ++x)
	{
		for (int y = 0; y < h; ++y)
		{
			if (index_vec[x][y] != -1)
				continue;

			sf::Color color = image.getPixel(x, y);

			if (color == sf::Color::White)
				continue;

			Rect rect(x, y, x, y);
			vector<sf::Vector2i> que;
			que.emplace_back(x, y);

			for (int i = 0; i < que.size(); ++i)
			{
				sf::Vector2i pos = que[i];
				index_vec[pos.x][pos.y] = index;
				rect.merge(Rect(pos.x, pos.y, pos.x, pos.y));

				if (pos.x + 1 < w && index_vec[pos.x + 1][pos.y] == -1 && image.getPixel(pos.x + 1, pos.y) == color)
				{
					que.emplace_back(pos.x + 1, pos.y);
					index_vec[pos.x + 1][pos.y] = -2;
				}

				if (pos.y + 1 < h && index_vec[pos.x][pos.y + 1] == -1 && image.getPixel(pos.x, pos.y + 1) == color)
				{
					que.emplace_back(pos.x, pos.y + 1);
					index_vec[pos.x][pos.y + 1] = -2;
				}

				if (pos.x - 1 >= 0 && index_vec[pos.x - 1][pos.y] == -1 && image.getPixel(pos.x - 1, pos.y) == color)
				{
					que.emplace_back(pos.x - 1, pos.y);
					index_vec[pos.x - 1][pos.y] = -2;
				}

				if (pos.y - 1 >= 0 && index_vec[pos.x][pos.y - 1] == -1 && image.getPixel(pos.x, pos.y - 1) == color)
				{
					que.emplace_back(pos.x, pos.y - 1);
					index_vec[pos.x][pos.y - 1] = -2;
				}
			}

			++rect.x2;
			++rect.y2;

			cout << index << ". ";
			rect.print();
			cout << '\n';

			rect.move(rectangle.getPosition().x, rectangle.getPosition().y);
			
			provinces_vec.emplace_back(rect);

			++index;
		}
	}
}

void printColor(sf::Color &color)
{
	cout << "( " << (int)color.r << ", " << (int)color.g << ", " << (int)color.r << " )";
}

int Map::updateProvinceId(int x, int y)
{
	x -= rectangle.getPosition().x;
	y -= rectangle.getPosition().y;

	if (x < 0 || image.getSize().x <= x || y < 0 || image.getSize().y <= y)
		return -1;

	active_province_id = index_vec[x][y];
	return active_province_id;
}

void Map::draw(sf::RenderWindow &window) const
{
	window.draw(rectangle);

	/*
	for (auto& province : provinces_vec)
	{
		province.draw(window);
	}
	//*/
	
	if (0 <= active_province_id)
		provinces_vec[active_province_id].draw(window);
}