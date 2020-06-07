#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class CheckBox
{
private:
    sf::Vector2f position;
    sf::Vector2f size;

    sf::RectangleShape button;
    sf::RectangleShape active;
    sf::Font font;
    sf::Text txt;

    bool status;

public:
    CheckBox(sf::Vector2f pos, std::string text);
    ~CheckBox(void);

public:
    void draw();
    bool isClick();

    void drawInPlace(sf::Vector2f pos);
    void setPosition(sf::Vector2f pos) { button.setPosition(pos); active.setPosition(pos.x+size.y*0.2,pos.y+size.y*0.2); txt.setPosition(pos.x+size.y+8,pos.y+1); }

    std::string getString() { return txt.getString(); }

    bool getStatus() { return status; }
    void setStatus(bool s) { status = s; }

private:
    bool isCursorOverCheckBox();
};

