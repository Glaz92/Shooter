#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "EnumClasses.h"

class GameMenu
{
private:
    sf::Text title;
    sf::Text stat;

    sf::RectangleShape shapeTmp;

    Button Bresume;
    Button BtryAgain;
    Button BnextLevel;
    Button BrestartLevel;
    Button BmainMenu;
    Button BquitGame;

public:
    GameMenu();
    ~GameMenu();

public:
    void setPosition();
    GameEngineState pause();
    State deadPlayer();

private:

};