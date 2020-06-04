#include "BackPack.h"
#include "Window.h"
#include <sstream>
#include <map>
#include <tuple>

BackPack::BackPack()
    : pistolAmmo(24), pistolMag(12), shotgunAmmo(0), shotgunMag(8), uziAmmo(30), uziMag(30),
    mgAmmo(0), mgMag(30), inHand(Weapon::Pistol), box(sf::Vector2f(230,120)),
    position(20, sf::VideoMode::getDesktopMode().height - 140)
{
    box.setFillColor(sf::Color(10, 10, 10, 140));
    font.loadFromFile("data/font/CodenameCoderFree4F-Bold.ttf");
    txt.setFont(font);
    txtAmmo.setFont(font);
    
    txt.setString("Pistol\n10/15");

    boxS.setTexture(GetWindow().getBoxRT().getTexture());
    life.setFont(font);
}

BackPack::~BackPack()
{
}

void BackPack::draw(int playerLife)
{
    box.setPosition(GetWindow().getViewCenter().x-sf::VideoMode::getDesktopMode().width/2+position.x,GetWindow().getViewCenter().y-sf::VideoMode::getDesktopMode().height/2+position.y);
    txt.setPosition(box.getPosition().x+35,box.getPosition().y+20);

    boxS.setPosition(GetWindow().getViewCenter().x+sf::VideoMode::getDesktopMode().width/2-position.x-240,GetWindow().getViewCenter().y-sf::VideoMode::getDesktopMode().height/2+position.y+30);
    life.setPosition(boxS.getPosition().x+20,boxS.getPosition().y+25);

    txt.setString(getWeaponInfoString());

    std::ostringstream ss;
    ss.str("");
    ss << "     " << playerLife / 2;
    life.setString(ss.str());

    GetWindow().draw(&box);
    GetWindow().draw(&txt);
    GetWindow().draw(&boxS);
    GetWindow().draw(&life);

    ss.str("");
//    ss << SCORE;
    txt.setString(ss.str());
    txt.setPosition(GetWindow().getViewCenter().x, GetWindow().getViewCenter().y - GetWindow().getSize().y / 2);
    GetWindow().draw(&txt);
}

std::string BackPack::getWeaponInfoString()
{
    std::ostringstream ss;
    using ammoInformation = std::tuple<std::string, int, int>;
    std::map<Weapon, ammoInformation> ammunictionMap { { Weapon::Pistol, { "Pistol", pistolMag, pistolAmmo } },
                                                       { Weapon::Shotgun, { "Shotgun", shotgunMag, shotgunAmmo } },
                                                       { Weapon::Uzi, { "Uzi", uziMag, uziAmmo } },
                                                       { Weapon::MG, { "MG", mgMag, mgAmmo } } };

    ss << std::get<0>(ammunictionMap[inHand]) << std::endl 
       << std::get<1>(ammunictionMap[inHand]) << "/" 
       << std::get<2>(ammunictionMap[inHand]);
    
    return ss.str();
}

bool BackPack::shot()
{
    std::map<Weapon, int*> magMap { { Weapon::Pistol, &pistolMag },
                                    { Weapon::Shotgun, &shotgunMag },
                                    { Weapon::Uzi, &uziMag },
                                    { Weapon::MG, &mgMag } }; 

    if(*magMap[inHand] > 0)
    {
        (*magMap[inHand])--;
        return true;
    }

    return false;
}

int BackPack::reload()
{
    std::map<Weapon, int> maxBulletsInMag { { Weapon::Pistol, 12 },
                                            { Weapon::Shotgun, 8 },
                                            { Weapon::Uzi,30 },
                                            { Weapon::MG, 30 } };

    std::map<Weapon, int*> magMap { { Weapon::Pistol, &pistolMag },
                                    { Weapon::Shotgun, &shotgunMag },
                                    { Weapon::Uzi, &uziMag },
                                    { Weapon::MG, &mgMag } }; 

    std::map<Weapon, int*> ammoMap { { Weapon::Pistol, &pistolAmmo },
                                     { Weapon::Shotgun, &shotgunAmmo },
                                     { Weapon::Uzi, &uziAmmo },
                                     { Weapon::MG, &mgAmmo } };

    if(*magMap[inHand] == maxBulletsInMag[inHand])
    {
        return 0;
    }
    else
    {
        if(*ammoMap[inHand] - (maxBulletsInMag[inHand] - *magMap[inHand]) >= 0)
        {
            *ammoMap[inHand] += *magMap[inHand] - maxBulletsInMag[inHand];
            *magMap[inHand] = maxBulletsInMag[inHand];
        }
        else if(*ammoMap[inHand] == 0)
        {
            return 0;
        }
        else
        {
            *magMap[inHand] += *ammoMap[inHand];
            *ammoMap[inHand] = 0;
        }

        return 120;
    }

    return 0;
}

void BackPack::setWeapon(Weapon weapon)
{
    inHand = weapon;
}

void BackPack::nextWeapon()
{
    std::map<Weapon, Weapon> nextWeapon { { Weapon::Pistol, Weapon::Shotgun },
                                          { Weapon::Shotgun, Weapon::Uzi },
                                          { Weapon::Uzi, Weapon::MG },
                                          { Weapon::MG, Weapon::Pistol } };

    inHand = nextWeapon[inHand];
}

void BackPack::prevWeapon()
{
    std::map<Weapon, Weapon> nextWeapon { { Weapon::Pistol, Weapon::MG },
                                          { Weapon::Shotgun, Weapon::Pistol },
                                          { Weapon::Uzi, Weapon::Shotgun },
                                          { Weapon::MG, Weapon::Uzi } };

    inHand = nextWeapon[inHand];
}