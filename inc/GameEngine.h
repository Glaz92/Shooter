#pragma once

#include "GameState.h"
#include <SFML/Audio.hpp>
#include <memory>
#include <list>
#include "Element.h"
#include "Player.h"
#include "Textures.h"
#include "MouseAim.h"
#include "Character.h"
#include "Bullet.h"
#include "BackPack.h"
#include "BloodAnimation.h"
#include "Button.h"
#include "Messages.h"
#include "Item.h"
#include "Score.h"
#include "GameMenu.h"
#include "EnumClasses.h"
#include "Map.h"

class GameEngine : public GameState
{
private:
    b2World world;
    std::string playerName;
    int reloadTime;
    GameEngineState state;
    Cmessages messages;

    sf::RectangleShape reloadBar;
    sf::View view;
    std::vector<BloodAnimation> blood;
    std::list<Bullet> bullets;
    std::shared_ptr<Player> player;
    Textures textures;
    MouseAim aim;
    std::vector<Character> characters;
    BackPack backPack;
    sf::Sound sound;                
    sf::Sound footstep;
    sf::Music backMusic;
    Score score;

    float timeStep;
    float deltaCam;

    sf::Clock clock;
    GameMenu gameMenu;
    Map map;
    Sounds sounds;

public:
    GameEngine(std::string _playerName);
    ~GameEngine();

public:
    State run();
    std::string getName() const;

private:
    void draw();
    void loadFromFile();

    void selectWeapon();
    void shot();
    void newBullets(int & timeShot);

    State game();
    State pause();
    State deadPlayer();
    State endLevel();

    void setView();
    void gameLogic();
    bool clockRestart();
    void control();
    void checkGameStatus();
};

