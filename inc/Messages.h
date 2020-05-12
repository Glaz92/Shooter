#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Cmessages
{
private:
    int time;
    sf::Text txt;
    unsigned int MAX;
    float rozX;
    float rozY;
    sf::RectangleShape shape;

    std::vector<std::string> message;
    std::vector<sf::Color> colorM;
    std::vector<bool> isEmpty;
    sf::Font font;
    float pos;

public:
    Cmessages(float xx, float yy);
    ~Cmessages();

public:
    void draw();
    void addMessage(std::string text, sf::Color ccc);
    void addEmptyMessage();
    void erase();
};

