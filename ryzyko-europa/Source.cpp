#include "GameManager.h"
#include "Map.h"
#include "Gui.h"

int main()
{
	sf::Font font;
	font.loadFromFile("arial.ttf");

	Map map;
	map.init(font);

	Gui gui(font);

	GameManager game_manager(font);

	sf::RenderWindow window(sf::VideoMode(1280, 720, 32U), "ryzyko-europa", sf::Style::Close);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				GuiCompType type = gui.handleEvent(event);

				switch (type)
				{
				case GuiCompType::Butt1: // Exchange cards
					cout << "Exchange cards\n";
					break;
				case GuiCompType::Butt2: // Next turn
					game_manager.nextTurn();
					cout << "Next turn\n";
					break;
				case GuiCompType::NumInp1:
					cout << "NumInp1\n";
					break;
				case GuiCompType::NumInp2:
					cout << "NumInp2\n";
					break;
				case GuiCompType::NumInp3:
					cout << "NumInp3\n";
					break;
				default:
				{
					int id = map.updateActiveProvince(event.mouseButton.x, event.mouseButton.y, true);
					cout << "Clicked province id: " << id << '\n';

					break;
				}
				}
			}
		}

		window.clear(sf::Color::White);

		map.draw(window);
		gui.draw(window);
		game_manager.draw(window);

		window.display();
	}

	// system("pause");

	return 0;
}