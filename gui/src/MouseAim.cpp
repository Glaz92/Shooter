#include "MouseAim.h"
#include "Window.h"

MouseAim::MouseAim()
    : top(sf::Vector2f(2,15)), bottom(sf::Vector2f(2,15)), left(sf::Vector2f(15,2)), right(sf::Vector2f(15,2)), delta(0)
{
    top.setOrigin(1,18);
    bottom.setOrigin(1,-3);
    left.setOrigin(18,1);
    right.setOrigin(-3,1);
}

MouseAim::~MouseAim()
{
}

void MouseAim::draw()
{
    pos.x = GetWindow().getMousePosition().x + GetWindow().getViewCenter().x - GetWindow().getSize().x / 2;
    pos.y = GetWindow().getMousePosition().y + GetWindow().getViewCenter().y - GetWindow().getSize().y / 2;
    delta -= delta > 0 ? 1 : 0;

    top.setPosition(pos.x,pos.y-delta);
    bottom.setPosition(pos.x,pos.y+delta);
    left.setPosition(pos.x-delta,pos.y);
    right.setPosition(pos.x+delta,pos.y);

    GetWindow().draw(&top);
    GetWindow().draw(&bottom);
    GetWindow().draw(&left);
    GetWindow().draw(&right);
}