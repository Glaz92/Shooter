#pragma once

#include "Player.h"
#include "EnumClasses.h"

class BackPack
{
private:
    int pAmmo;
    int pMag;
    int sAmmo;
    int sMag;
    int uAmmo;
    int uMag;
    int mAmmo;
    int mMag;
    Weapon inHand;
    sf::RectangleShape box;
    sf::Vector2f position;

    sf::Text life;
    sf::Sprite boxS;
    sf::Font font;
    sf::Text txt;
    sf::Text txtAmmo;

public:
    BackPack();
    ~BackPack();

public:
    Weapon getHand() { return inHand; }
    float getWeaponScore() { return static_cast<float>(inHand); }

    bool shot();
    int reload();
    void setWeapon(Weapon weapon);

    void nextWeapon();
    void prevWeapon();

    void draw(int playerLife);

private:
    std::string getWeaponInfoString();
};

