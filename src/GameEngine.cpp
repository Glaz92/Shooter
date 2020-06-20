#include "GameEngine.h"
#include "Window.h"
#include "MapLoader.h"
#include <map>
#include <tuple>
#include <algorithm>

GameEngine::GameEngine(std::string _playerName)
    : world(b2Vec2(0,0)), playerName(_playerName), reloadTime(0), state(GameEngineState::Game),
    messages(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)
{
    footstep.setBuffer(sounds.Sfoot);

    MapLoader mapLoader;
    mapLoader.loadFromFile(_playerName, player, world, map, characters, textures);
    view = GetWindow().getView();

    reloadBar.setFillColor(sf::Color::Red);

    score.reset();
    
//    backMusic.openFromFile("data\\sounds\\background.wav");
//    backMusic.setLoop(true);
//    backMusic.play();

    timeStep = 1.0f / 60.0f;
    deltaCam = 0;
}

GameEngine::~GameEngine(void)
{
}

State GameEngine::run()
{
    draw();

    switch(state)
    {
    case GameEngineState::Game:
        return game();
    case GameEngineState::Pause:
        return pause();
    case GameEngineState::DeadPlayer:
        return deadPlayer();
    case GameEngineState::EndLevel:
        return endLevel();
    default:
        return State::MainMenu;
    }
}

std::string GameEngine::getName() const
{
    return playerName;
}

State GameEngine::game()
{
    if(!clockRestart()) return State::Game;

    control();
    shot();
    gameLogic();
    setView();
    checkGameStatus();

    return State::Game;
}

bool GameEngine::clockRestart()
{
    if(clock.getElapsedTime().asMilliseconds()<16)
        return false;
    
    clock.restart();
    return true;
}

void GameEngine::control()
{
    player->control();
    selectWeapon();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        while(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            state = GameEngineState::Pause;
}

void GameEngine::checkGameStatus()
{
    if(player->getLife() < 1)
    {
        state = GameEngineState::DeadPlayer;
    }

    if(map.isEndPoint(player->getPosition()))
    {
        state = GameEngineState::EndLevel;
    }
}

void GameEngine::gameLogic()
{
    for(auto it = bullets.begin(); it != bullets.end(); it++)
    {
        if(it->getLifeTime() > MAX_BULLET_LIFETIME)
        {
            auto tmp = it--;
            bullets.erase(tmp);
        }
        else
        {        
            it->logic(blood, *player);
        }
    }

    auto behaviour = [&](auto & character)
    {
        character.behavior(*player, bullets, characters, map.getElementsMid());
    };

    std::for_each(characters.begin(), characters.end(), behaviour);

    world.Step(timeStep, 8, 3);
    score.calculateMultiple();
}

void GameEngine::setView()
{    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if(deltaCam < 340)
            deltaCam += 15;
    }
    else
    {
        if(deltaCam>0)
            deltaCam-=15;
    }

    view.setCenter(player->getPosition().x+cos(deg2rad(player->getRot()))*deltaCam,player->getPosition().y+sin(deg2rad(player->getRot()))*deltaCam);

    GetWindow().setView(view);
}

State GameEngine::pause()
{
    state = gameMenu.pause();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        while(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            state = GameEngineState::Game;

    return State::Game;
}

State GameEngine::deadPlayer()
{
    return gameMenu.deadPlayer();
}

State GameEngine::endLevel()
{
    return State::MainMenu;
}

void GameEngine::draw()
{
    map.drawBackground();

    auto drawElement = [](auto & element) { element.draw(); };
    auto drawDeadCharacter = [](auto & character) { character.drawIfDead(); };
    auto drawAliveCharacter = [](auto & character) { character.drawIfAlive(); };

    std::for_each(blood.begin(), blood.end(), drawElement);
    std::for_each(characters.begin(), characters.end(), drawDeadCharacter);
    map.drawElementsMid();
    std::for_each(bullets.begin(), bullets.end(), drawElement);

    player->draw(view);

    std::for_each(characters.begin(), characters.end(), drawAliveCharacter);
    map.drawElementsTop();

    backPack.draw(player->getLife());

    if(reloadTime>0)
    {
        reloadBar.setPosition(player->getPosition().x, player->getPosition().y-40);
        GetWindow().draw(&reloadBar);
    }

    messages.draw();

    aim.draw();
}

void GameEngine::selectWeapon()
{
    std::map<Weapon, int> weaponToInt { { Weapon::Pistol, 1 },
                                        { Weapon::Shotgun, 2 },
                                        { Weapon::Uzi, 3 },
                                        { Weapon::MG, 4 }};

    auto setWeapon = [&](Weapon w) { backPack.setWeapon(w);
                                     player->setWeapon(weaponToInt[w]); };

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) setWeapon(Weapon::Pistol);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) setWeapon(Weapon::Shotgun);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) setWeapon(Weapon::Uzi);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) setWeapon(Weapon::MG);
}

void GameEngine::shot()
{
    static int timeShot = 0;

    if(reloadTime > 0)
    {
        reloadTime--;
        reloadBar.setSize(sf::Vector2f(reloadTime,20));
        reloadBar.setOrigin(reloadTime/2,20);
    }
    else if(timeShot>0)
    {
        timeShot--;
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        newBullets(timeShot);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        reloadTime = backPack.reload();
    }
}

void GameEngine::newBullets(int & timeShot)
{
    auto createBullet = [&](auto s, auto delta, auto time)
    {
        int num = backPack.getHand() == Weapon::Shotgun ? 5 : 1;
        sound.setBuffer(*s);
        sound.play();
        for(int i = 0, d = -6; i < num; i++, d += 3)
            bullets.push_back(Bullet(sf::Vector2f(player->getPosition().x + cos(deg2rad(player->getRot() + 10)) * 10,
                                                  player->getPosition().y + sin(deg2rad(player->getRot() + 10)) * 10),
                                     40, player->getRot() + (num != 1 ? d : (aim.getDelta() / 2.5f * (rand() % 3 - 1))),
                                     world, characters, map.getElementsMid()));
        aim.setDelta(delta);
        timeShot = time;
    };

    using InputData = std::tuple<sf::SoundBuffer*, int, int>;
    std::map<Weapon, InputData> inputDataMap { { Weapon::Pistol, { &sounds.Sgun, 12, 24 } },
                                               { Weapon::Shotgun, { &sounds.Sshotgun, 20, 24 } },
                                               { Weapon::Uzi, { &sounds.Suzi, 15, 9 } },
                                               { Weapon::MG, { &sounds.Smg, 18, 5 } } };

    if(backPack.shot())
    {
        createBullet(std::get<0>(inputDataMap[backPack.getHand()]),
                     std::get<1>(inputDataMap[backPack.getHand()]),
                     std::get<2>(inputDataMap[backPack.getHand()]));
    }
}