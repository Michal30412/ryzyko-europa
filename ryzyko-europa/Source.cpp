#include "GameManager.h"

int main()
{
	srand(time(NULL));

	sf::Font font;
	font.loadFromFile("arial.ttf");

	Map map;
	map.init(font);

	Gui gui(font);

	GameManager game_manager(&map, &gui, font);

	sf::RenderWindow window(sf::VideoMode(1280, 720, 32U), "ryzyko-europa", sf::Style::Close);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();			

			game_manager.handleEvent(event);
		}

		window.clear(sf::Color::White);

		game_manager.draw(window);

		window.display();
	}

	// system("pause");

	return 0;
}