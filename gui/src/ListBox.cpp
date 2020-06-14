#include "ListBox.h"
#include "Window.h"

ListBox::ListBox(sf::Vector2f s,sf::Vector2f pos)
    : mapplace(s), bar(sf::Vector2f(15,s.y)), barElement(sf::Vector2f(15,s.y)), position(pos), size(s), begin(0), select(""),
    scrollUp(sf::Vector2f(13,13)), scrollDown(sf::Vector2f(13,13)), drawPos(pos)
{
    mapplace.setOutlineThickness(2);
    mapplace.setOutlineColor(sf::Color::Black);
    mapplace.setFillColor(sf::Color(130,130,130));
    mapplace.setPosition(pos.x,pos.y);

    bar.setFillColor(sf::Color(90,90,90,160));
    barElement.setFillColor(sf::Color(40,40,40,160));
    bar.setPosition(pos.x+size.x-15,pos.y);
    barElement.setPosition(pos.x+size.x-15,pos.y+15);

    scrollUp.setOutlineThickness(2);
    scrollUp.setOutlineColor(sf::Color::Black);
    scrollUp.setFillColor(sf::Color(40,40,40,160));
    scrollUp.setPosition(position.x+size.x-13,position.y);

    scrollDown.setOutlineThickness(2);
    scrollDown.setOutlineColor(sf::Color::Black);
    scrollDown.setFillColor(sf::Color(40,40,40,160));
    scrollDown.setPosition(position.x+size.x-13,position.y+size.y-13);
}

ListBox::~ListBox(void)
{
}

bool ListBox::isClick()
{
    for(int i=0;i<end;i++)
    {
        elementButton[i+begin]->drawInPlace(sf::Vector2f(position.x + 5, position.y + i * 30),
                                            sf::Vector2f(drawPos.x + 5, drawPos.y + i * 30));
        if(elementButton[i+begin]->isClick())
        {
            select = elementButton[i+begin]->getString();
            return true;
        }
    }

    scroll();

    return false;
}

float ListBox::getElementSizeDiv()
{
    return static_cast<float>(elementButton.size()) /
           static_cast<float>(static_cast<int>(size.y / 30));
} 

void ListBox::setElementsPositions()
{
    if((elementButton.size() * 30) > size.y)
    {
        barElement.setSize(sf::Vector2f(15,(size.y - 30) / getElementSizeDiv()));
        end = int(size.y / 30);
    }
    else
    {
        barElement.setSize(sf::Vector2f(15, size.y - 40));
        barElement.setPosition(drawPos.x+size.x - 15, drawPos.y + 15);
        end = elementButton.size();
    }

    mapplace.setPosition(drawPos);
    scrollUp.setPosition(drawPos.x + size.x - 13,drawPos.y);
    scrollDown.setPosition(drawPos.x + size.x - 13, drawPos.y+size.y - 13);
    bar.setPosition(drawPos.x + size.x - 15, drawPos.y);
}

void ListBox::draw()
{
    setElementsPositions();
    GetWindow().draw(&mapplace);
    GetWindow().draw(&bar);
    GetWindow().draw(&barElement);
    GetWindow().draw(&scrollUp);
    GetWindow().draw(&scrollDown);
}

void ListBox::addElement(std::string name)
{
    sf::Vector2f pos { position.x + 5, position.y + elementButton.size() * 30 };
    sf::Vector2f size { size.x - 20, 30 };
    elementButton.push_back(std::make_unique<Button>(pos, name, size));
}

void ListBox::scroll()
{
    scrollUp.setFillColor(sf::Color(40,40,40,160));
    scrollDown.setFillColor(sf::Color(40,40,40,160));
    if(GetWindow().getMousePosition().x>(position.x+size.x-15) && GetWindow().getMousePosition().x<(position.x+size.x))
    {
        float delta = (((size.y - 30) - ((size.y - 30) / getElementSizeDiv()))) / static_cast<float>(elementButton.size() - static_cast<int>(size.y/30));

        if(GetWindow().getMousePosition().y<position.y+20 && GetWindow().getMousePosition().y>position.y)
        {
            scrollUp.setFillColor(sf::Color(60,120,180));
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                if(begin>0)
                {
                    barElement.move(0, -delta);
                    begin--;
                }
            }

        }
        else if(GetWindow().getMousePosition().y>(position.y+size.y-20) && GetWindow().getMousePosition().y<(position.y+size.y))
        {
            scrollDown.setFillColor(sf::Color(60,120,180));
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                if((begin + static_cast<int>(size.y / 30)) < static_cast<int>(elementButton.size()))
                {
                    barElement.move(0, delta);
                    begin++;
                }
            }

        }

    }
}

void ListBox::rescale(float x)
{
    x = x > 2 ? 2 : 1;
}