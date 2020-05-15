#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

class TxtBox
{
private:
    bool input;
    sf::RectangleShape box;
    sf::Vector2f position;
    sf::Vector2f size;
    bool active;
    bool onlyNum;

    sf::Font font;
    sf::Text txt;
    std::ostringstream ss;

private:
    void inputTxt();

public:
    TxtBox(sf::Vector2f s, sf::Vector2f pos, bool in, bool onlyNumbers);
    ~TxtBox(void);

public:
    void setString(std::string txt) { if(!active) { ss.str(""); ss << txt; } }
    void draw();

    std::string getString() { return txt.getString(); }
    bool getStatus() { return active; }

    void setAcvite(bool b) { active = b; }
    void setInput(bool in) { input = in; }
    void setPosition(sf::Vector2f pos) { box.setPosition(pos); txt.setPosition(pos.x+5,pos.y+3); }

    void rescale(float x);
};

