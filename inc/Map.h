#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Element.h"
#include "Window.h"

class Map
{
private:
    sf::Vector2f endPoint;
    std::vector<Element> ElementsMid;
    std::vector<Element> ElementsTop;

    sf::RenderTexture background;
    sf::Sprite backgroundSprite;

public:
    std::vector<Element> & getElementsMid() { return ElementsMid; }

    void drawElementsMid() { for(auto & x : ElementsMid) x.draw(); }
    void drawElementsTop() { for(auto & x : ElementsTop) x.draw(); }
    void drawBackground() { GetWindow().draw(&backgroundSprite); }

    bool isEndPoint(const sf::Vector2f & point) { return abs(point.x - endPoint.x) < 32 && abs(point.y - endPoint.y) < 32; }

    friend class MapLoader;
};