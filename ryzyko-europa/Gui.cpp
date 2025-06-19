#include "Gui.h"

Gui::Gui(sf::Font &font)
{
	vec.push_back(new Button(10, 10 + 0 * 60, 150, 50, L"Rekrutacja", font));
	vec.push_back(new Button(10, 10 + 1 * 60, 150, 50, L"Przesuñ", font));
	vec.push_back(new Button(10, 10 + 2 * 60, 150, 50, L"Atakuj", font));
	vec.push_back(new Button(10, 10 + 3 * 60, 150, 50, L"Wymieñ karty", font));
	vec.push_back(new Button(10, 10 + 4 * 60, 150, 50, L"Nastêpna tura", font));

	// vec.push_back(new CheckBox(10, 10 + 5 * 60, 50, 50, true));
	// vec.push_back(new CheckBox(10, 10 + 6 * 60, 50, 50, true));
}

Gui::~Gui()
{
	for (auto pt : vec)
		delete pt;
}

GuiComponent* Gui::getComponent(int index)
{
	return vec.at(index);
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

void Gui::draw(sf::RenderWindow &window)
{
	for (auto pt : vec)
		pt->draw(window);
}