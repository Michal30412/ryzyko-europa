#include <vld.h>
#include "Map.h"
#include "Gui.h"

int main()
{
	sf::Font font;
	font.loadFromFile("arial.ttf");

	Map map;
	map.init(font);

	Gui gui(font);

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
				case GuiCompType::Butt1:
					cout << "Butt1\n";
					break;
				case GuiCompType::Butt2:
					cout << "Butt2\n";
					break;
				case GuiCompType::Butt3:
					cout << "Butt3\n";
					break;
				case GuiCompType::Butt4:
					cout << "Butt4\n";
					break;
				case GuiCompType::Butt5:
					cout << "Butt5\n";
					break;
				case GuiCompType::NumInp1:
					cout << "NumInp1\n";
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

		window.clear(sf::Color::Black);

		map.draw(window);
		gui.draw(window);

		window.display();
	}

	// system("pause");

	return 0;
}