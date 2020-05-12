#pragma once

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

    b2Body * getBody() { return body; }

    sf::Vector2f getPosition() { return position; }
    float getRot() { return character.getRotation(); }

    void setWeapon(int i) { character.setTextureRect(sf::IntRect(i*64,0,64,64)); }

    int getLife() { return life; }

    void setLife(int x) { life = x; }

    void changeLife(int x) 
    { 
        life += x; 
        if(life>200) life = 200; 
        if(life<1)
        {
            life = 0;
            character.setTextureRect(sf::IntRect(0,64,128,64));
        }
    
    }

};


