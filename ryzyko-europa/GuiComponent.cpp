#include "GuiComponent.h"

GuiComponent::GuiComponent() : GuiComponent(0, 0, 0, 0)
{
	;
}

GuiComponent::GuiComponent(int _x, int _y, int _w, int _h)
{
	setRectangle(_x, _y, _w, _h);
}

bool GuiComponent::posIn(const sf::Vector2i &pos)
{
	return x <= pos.x && pos.x <= x + w && y <= pos.y && pos.y <= y + h;
}

void GuiComponent::setPosition(int _x, int _y)
{
	x = _x;
	y = _y;

	shape.setPosition(x, y);
}

void GuiComponent::setRectangle(int _x, int _y, int _w, int _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;

	shape.setPosition(x, y);
	shape.setSize({ (float)w, (float)h });
}