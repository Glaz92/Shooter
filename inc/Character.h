#pragma once

#include "Textures.h"
#include "Player.h"
#include "Bullet.h"
#include "Element.h"
#include "Sounds.h"
#include "EnumClasses.h"
#include <list>

class Bullet;

class Character
{
private:
    sf::Vector2f position;
    float rot;
    Textures & textures;
    std::string textureFileName;
    bool anim;
    unsigned int point;
    b2World & world;
    int animStep;
    std::vector<sf::Vector2f> points;
    sf::IntRect rect;
    int alarm;
    int waitTime;
    float speed;
    bool down;
    bool dead;
    int life;
    int timeShot;
    int reloadTime;
    int ammo;
    Weapon weapon;

    sf::Sound sound;
    std::vector<sf::Vector2f> tmpPoints;
    sf::Sprite character;
    b2Body * body;
    Sounds sounds;


public:
    Character(b2World & _world, sf::Vector2f _position, float _rot, Textures & _textures, std::string fileName, sf::IntRect _rect, bool _anim, int _animStep, std::vector<sf::Vector2f> _points);
    ~Character();

public:
    void drawIfDead() { if(dead) draw(); }
    void drawIfAlive() { if(!dead) draw(); }

    void setAlarm(int x) { alarm = x; }
    void setRot(float _rot) { rot = _rot; }

    void behavior(Player & player, std::list<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements);

    sf::Vector2f getPosition() { return position; }

    void changeLife(int x) { life += x; if(life < 1) isDead(); }
    bool ifDead() { return dead; }

private:
    bool isPointAvaible(sf::Vector2f point, std::vector<Character> & characters, std::vector<Element> & Elements);
    void isDead() { world.DestroyBody(body);  dead = true; character.setTextureRect(sf::IntRect(0,64,128,64)); character.setOrigin(64,32); } 
    void shot(std::list<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements);
    void draw();

    float calculateRotToPoint(const sf::Vector2f & point);
    void setRotToPoint(const sf::Vector2f & point);
    void setBodyLinearVelocity(const sf::Vector2f & point);

    void setAlarmIfSeePlayer(Player & player, std::vector<Character> & characters, std::vector<Element> & Elements);
    void unAlarmedMoveBehavior();
    void backToPosition();
    void patrolMoving();

    void unAlarmedBehavior(Player & player, std::vector<Character> & characters, std::vector<Element> & Elements);

    void alarmedSeePlayer(Player & player, std::list<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements);
    void alarmedDoNotSeePlayer();

    void alarmedBehavior(Player & player, std::list<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements);
};

