#include <vld.h>
#include "Map.h"

int main()
{
	// sf::Font font;
	// font.loadFromFile("");

	Map map;
	map.analyzeImage();

	sf::RenderWindow window(sf::VideoMode(1280, 720, 32U), "ryzyko-europa", sf::Style::Close);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
				cout << "Clicked province id: " << map.updateProvinceId(event.mouseButton.x, event.mouseButton.y) << '\n';
		}

		window.clear(sf::Color::Black);

		map.draw(window);

		window.display();
	}

	// system("pause");

	return 0;
}