#include "Item.h"
#include "Window.h"
#include <sstream>

Item::Item(Textures & _textures, sf::Vector2f _position, sf::IntRect rect)
    : textures(_textures), position(_position), isExist(true)
{

    item.setTexture(*textures.characters["item.png"]);

    item.setOrigin(16,16);

    item.setTextureRect(rect);

    if(rect.top == 0)
    {
        if(rect.left == 0)
            type = 0;
        else
            type = 1;
    }
    else if(rect.top == 32)
    {
        if(rect.left == 0)
            type = 2;
        else
            type = 3;
    }
    else
    {
        type = 4;    
    }

}


Item::~Item(void)
{
}

void Item::draw()
{
    if(isExist)
    {
        item.setPosition(position);

        GetWindow().draw(&item);
    }
}

void Item::setRect(sf::IntRect rect)
{

    item.setTextureRect(rect);

    if(rect.top == 0)
    {
        if(rect.left == 0)
            type = 0;
        else
            type = 1;
    }
    else if(rect.top == 32)
    {
        if(rect.left == 0)
            type = 2;
        else
            type = 3;
    }
    else
    {
        type = 4;    
    }
}

std::string Item::getString()
{
    std::ostringstream ss;
    ss.str("");

    ss << position.x << " " << position.y << " " << item.getTextureRect().left << " " << item.getTextureRect().top << " "
        << item.getTextureRect().width << " " << item.getTextureRect().height << std::endl;

    return ss.str();
}