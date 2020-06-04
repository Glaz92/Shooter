#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "Button.h"

class ListBox
{
private:
    sf::RectangleShape mapplace;
    sf::RectangleShape bar;
    sf::RectangleShape barElement;
    sf::Vector2f position, size;
    int begin;
    std::string select;
    sf::RectangleShape scrollUp;
    sf::RectangleShape scrollDown;
    sf::Vector2f drawPos;

    int end;
    std::vector<std::unique_ptr<Button>> elementButton;

private:
    void scroll();

public:
    ListBox(sf::Vector2f s,sf::Vector2f pos);
    ~ListBox(void);

public:
    void draw();
    bool isClick();

    void addElement(std::string name);
    void clear() { elementButton.clear(); begin = 0; barElement.setPosition(position.x + size.x - 15, position.y + 15); }
    std::string getSelect() { return select; }

    void setPosition(sf::Vector2f pos) { drawPos = pos; }
    void rescale(float x);

private:
    void setElementsPositions();
    float getElementSizeDiv();
};

