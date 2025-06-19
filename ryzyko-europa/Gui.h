#ifndef GUI_H
#define GUI_H

#include "Button.h"
#include "NumberInput.h"

#include <vector>

using namespace std;

enum GuiCompType
{
	Butt1,
	Butt2,
	Butt3,
	Butt4,
	Butt5,
	Chbx1,
	Chbx2,
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
	void draw(sf::RenderWindow &window);
};

#endif