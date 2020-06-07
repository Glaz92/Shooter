#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
private:
    sf::Vector2f position;
    sf::Vector2f size;

    sf::RectangleShape button;
    sf::Text txt;

    sf::Color backColor;

    float speed;

public:
    Button(sf::Vector2f pos, std::string text);
    Button(sf::Vector2f pos, std::string text, sf::Vector2f s);
    Button(sf::Vector2f pos, std::string text, sf::Vector2f s, int font, int fontSize);
    Button(sf::Vector2f pos, std::string text, sf::Vector2f s, int font, int fontSize, sf::Color fontColor, sf::Color _backColor);
    ~Button();

public:
    void draw();
    bool isClick();
    bool isClickRight();

    bool isPressed();
    bool isPressedRight();

    void drawInPlace(sf::Vector2f pos);
    void drawInPlace(sf::Vector2f pos, sf::Vector2f drawPos);

    std::string getString() { return txt.getString(); }

    void setPosition(sf::Vector2f pos) { button.setPosition(pos); txt.setPosition(pos.x+10, pos.y+1); }

    void setString(std::string _txt) { txt.setString(_txt); }

    void rescale(float x);

private:
    bool isCursorOverButton();
};
