#ifndef GUI_H
#define GUI_H

#include "Button.h"
#include "NumberInput.h"

#include <vector>

using namespace std;

enum GuiCompType
{
	Butt1,
	NumInp1,
	NumInp2,
	NumInp3,
	NONE
};

class Gui
{
	vector<GuiComponent*> vec;
public:
	Gui(sf::Font &font);
	~Gui();
	GuiComponent* getComponent(int index);
	GuiCompType handleEvent(sf::Event &e);
	void draw(sf::RenderWindow &window, bool with);
};

#endif