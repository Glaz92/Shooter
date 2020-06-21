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
    GameEngineState pause();
    State deadPlayer();
    State endLevelMenu(const std::string playerName);

private:
    void pauseMenuDraw();
    GameEngineState pauseMenuButtons();

    void deadPlayerMenuDraw();
    State deadPlayerMenuButtons();

    void endLevelMenuDraw();
    State endLevelMenuButtons(const std::string playerName);

    void setNextLevel(const std::string playerName);
};