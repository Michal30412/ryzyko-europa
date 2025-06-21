#include "Gui.h"

Gui::Gui(sf::Font &font)
{
	vec.push_back(new Button(1280 - (1280 - 600) / 2 + 20, 720 - 100 + (100 - 50) / 2, 150, 50, "Next player", font));

	vec.push_back(new NumberInput(10, 10 + 5 * 60, 150, 50, 3, font));
	vec.push_back(new NumberInput(10, 10 + 6 * 60, 150, 50, 2, font));
	vec.push_back(new NumberInput(10, 10 + 7 * 60, 150, 50, 1, font));
}

Gui::~Gui()
{
	for (auto pt : vec)
		delete pt;
}

GuiComponent* Gui::getComponent(int index)
{
	return vec[index];
}

GuiCompType Gui::handleEvent(sf::Event &e)
{
	int i = 0;
	for (auto pt : vec)
	{
		if (pt->handleEvent(e))
			break;
		++i;
	}
	return (GuiCompType)i;
}

void Gui::draw(sf::RenderWindow &window, bool with)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		if (!with && i >= 1)
			break;

		vec[i]->draw(window);
	}
}