#pragma once

#include <memory>
#include "Window.h"
#include "Textures.h"
#include <Box2d/Box2d.h>

class Player
{
private:
    sf::Texture texture;
    sf::Sprite character;

    sf::Vector2f position;
    b2Body * body;

    float speed;

    int life;

public:
    Player(b2World & world, sf::Vector2f pos);
    ~Player();

public:
    void draw(sf::View & view);
    void control();

    sf::Vector2f getPosition() { return position; }
    float getRot() { return character.getRotation(); }

    void setWeapon(int i) { character.setTextureRect(sf::IntRect(i * 64, 0, 64, 64)); }

    int getLife() { return life; }

    void setLife(int x) { life = x; }

    void changeLife(int x);
};


