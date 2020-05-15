#include "CheckBox.h"
#include "Window.h"

CheckBox::CheckBox(sf::Vector2f pos, std::string text)
    : status(false)
{
    position=pos;

    button.setFillColor(sf::Color(130,130,130));
    button.setOutlineThickness(3);
    button.setOutlineColor(sf::Color(100,100,100));
    active.setFillColor(sf::Color(80,80,80));

    font.loadFromFile("data/font/calibri.ttf");
    txt.setFont(font);
    txt.setString(text);
    txt.setFillColor(sf::Color::Black);
    txt.setCharacterSize(15);

    size.x=txt.getGlobalBounds().height+txt.getGlobalBounds().width+20;
    size.y=txt.getGlobalBounds().height+10;

    button.setSize(sf::Vector2f(size.y,size.y));
    active.setSize(sf::Vector2f(size.y*0.6,size.y*0.6));
    button.setPosition(pos.x,pos.y);
    active.setPosition(pos.x+size.y*0.2,pos.y+size.y*0.2);
    txt.setPosition(pos.x+size.y+8,pos.y+1);

}


CheckBox::~CheckBox(void)
{
}


void CheckBox::draw()
{
    GetWindow().draw(&button);
    if(status)
        GetWindow().draw(&active);
    GetWindow().draw(&txt);
}

void CheckBox::drawInPlace(sf::Vector2f pos)
{
    position=pos;
    button.setPosition(pos.x,pos.y);
    txt.setPosition(pos.x,pos.y);
    GetWindow().draw(&button);
    GetWindow().draw(&txt);
}

bool CheckBox::isClick()
{
    button.setFillColor(sf::Color(130,130,130));
    if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
        if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
        {
            button.setFillColor(sf::Color(60,120,180));
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
                    if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
                    {
                        if(status)
                            status=false;
                        else
                            status=true;

                        return true;
                    }
            }
        }

    return false;
}