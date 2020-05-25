#include "Character.h"
#include "Window.h"
#include <sstream>
#include <algorithm>

Character::Character(b2World & _world, sf::Vector2f _position, float _rot, Textures & _textures, std::string fileName, sf::IntRect _rect, bool _anim, int _animStep, std::vector<sf::Vector2f> _points)
    : position(_position), rot(_rot), textures(_textures), textureFileName(fileName), anim(_anim), point(0), world(_world),
    animStep(_animStep), points(_points), rect(_rect), alarm(0), waitTime(rand()%300), speed(6), down(false), dead(false),
    life(50), timeShot(0), reloadTime(0), ammo(0), weapon(static_cast<Weapon>(rect.left/64))
{
    character.setTexture(*textures.characters[textureFileName]);

    character.setTextureRect(rect);
    character.setOrigin(32,32);
    character.setRotation(rot);
    character.setPosition(position);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody; 
    bodyDef.position.Set( position.x/64, position.y/64 );
    bodyDef.angularDamping = 2.0f;
    bodyDef.linearDamping = 120.0f; 

    body = world.CreateBody(&bodyDef);
         
    b2CircleShape bodyShape;
    bodyShape.m_radius = 0.3;

    body->CreateFixture(&bodyShape,1.0f);
}

Character::~Character(void)
{
}

void Character::draw()
{
    if(!dead)
    {
        position = sf::Vector2f(body->GetPosition().x*64,body->GetPosition().y*64);
        character.setPosition(position);
        character.setRotation(rot);
    }
    sf::Listener::setPosition(GetWindow().getViewCenter().x, GetWindow().getViewCenter().y,0);

    GetWindow().draw(&character);  
}

float Character::calculateRotToPoint(const sf::Vector2f & point)
{
    return -atan2(static_cast<float>(point.x - character.getPosition().x),
                  static_cast<float>(point.y - character.getPosition().y)) * 180 / 3.1415f + 90;
}

void Character::setRotToPoint(const sf::Vector2f & point)
{
    rot = calculateRotToPoint(point);
}

void Character::setBodyLinearVelocity(const sf::Vector2f & point)
{
    setRotToPoint(point);
    body->SetLinearVelocity(b2Vec2(cos(deg2rad(rot)) * speed, sin(deg2rad(rot)) * speed));
}

void Character::behavior(Player & player, std::list<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements)
{ 
    if(dead) return;

    waitTime--;
    if(alarm > 0)
    {
        alarmedBehavior(player, bullets, characters, Elements);
        alarm--;
    }
    else
    {
        unAlarmedBehavior(player, characters, Elements);
    }
}

void Character::setAlarmIfSeePlayer(Player & player, std::vector<Character> & characters, std::vector<Element> & Elements)
{
    if(isPointAvaible(player.getPosition(), characters, Elements))
    {
        float tmp = calculateRotToPoint(player.getPosition());

        if(character.getRotation() > tmp - 80 && character.getRotation() < tmp + 80)
        {
            alarm = 100 + rand() % 200;
            tmpPoints.push_back(player.getPosition());
        }
    }
}

void Character::unAlarmedMoveBehavior()
{
    backToPosition();
    patrolMoving();
}

void Character::backToPosition()
{
    if(tmpPoints.size() > 0)
    {
        if(calculateDistance(character.getPosition(), tmpPoints[tmpPoints.size() - 1]) < 15)
        {
            tmpPoints.pop_back();
        }
        else
        {
            setBodyLinearVelocity(tmpPoints[tmpPoints.size() - 1]);
        }
    }
}

void Character::patrolMoving()
{
    if(points.size() == 0)
    {
        if(calculateDistance(character.getPosition(), position) < 15)
        {
            if(waitTime < 10)
            {
                rot += (rand() % 4 - 2) * 70;
                waitTime = 60 + rand() % 500;
            }
        }
        else
        {
            setBodyLinearVelocity(position);
        }
    }
    else if(tmpPoints.size() == 0)
    { 
        if(calculateDistance(character.getPosition(), points[point]) < 15)
        {
            point++;
            if(point == points.size())
            {
                std::reverse(points.begin(), points.end());
                point = 0;
            }
        }
        else
        {
            setBodyLinearVelocity(points[point]);
        }
    }
}

void Character::unAlarmedBehavior(Player & player, std::vector<Character> & characters, std::vector<Element> & Elements)
{
    setAlarmIfSeePlayer(player, characters, Elements);
    unAlarmedMoveBehavior();
}

void Character::alarmedSeePlayer(Player & player, std::list<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements)
{
    constexpr int ALARM_MAX_VALUE = 450;

    if(calculateDistance(player.getPosition(), character.getPosition()) < 150)
    {
        shot(bullets,characters,Elements);
        alarm = ALARM_MAX_VALUE;
    }
    else
    {
        if(calculateDistance(player.getPosition(), character.getPosition()) < 550)
        {
            shot(bullets,characters,Elements);
        }
        if(tmpPoints.size() > 0 && calculateDistance(character.getPosition(), tmpPoints[tmpPoints.size()-1]) < 15)
        {
            tmpPoints.push_back(player.getPosition());
        }
        else
        {
            alarm = ALARM_MAX_VALUE;
            tmpPoints[tmpPoints.size()-1] = character.getPosition();
            tmpPoints.push_back(player.getPosition());
            setBodyLinearVelocity(tmpPoints[tmpPoints.size()-1]);
        }
    }
}

void Character::alarmedDoNotSeePlayer()
{
    if(tmpPoints.size() == 0)
    {
        tmpPoints.push_back(character.getPosition());
    }
    else if(!(tmpPoints.size()>0 && calculateDistance(character.getPosition(), tmpPoints[tmpPoints.size()-1]) < 15))
    {
        setBodyLinearVelocity(tmpPoints[tmpPoints.size()-1]);
    }
}

void Character::alarmedBehavior(Player & player, std::list<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements)
{
    setRotToPoint(player.getPosition());

    if(isPointAvaible(player.getPosition(), characters, Elements))
    {
        alarmedSeePlayer(player, bullets, characters, Elements);
    }
    else
    {
        alarmedDoNotSeePlayer();
    }
}

bool Character::isPointAvaible(sf::Vector2f point, std::vector<Character> & characters, std::vector<Element> & Elements)
{
    float tmpRot = calculateRotToPoint(point);
    Bullet visionTmp(character.getPosition(),0,tmpRot,world,characters,Elements);

    while(visionTmp.getLifeTime()<540)
    { 
        if(visionTmp.isPointAvaible(point.x, point.y))
            return true;
    }

    return false;
} 

void Character::shot(std::list<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements)
{
    sound.setPosition(position.x, position.y, 0);
    sound.setRelativeToListener(true);

    auto createBullet = [&](auto s, auto a, auto time)
    {
        if(ammo > a) reloadTime = 100;
        int num = weapon == Weapon::Shotgun ? 5 : 1;
        sound.setBuffer(*s);
        sound.play();
        for(int i = 0, d = -6; i < num; i++, d += 3)
            bullets.push_back(Bullet(sf::Vector2f(character.getPosition().x + cos(deg2rad(character.getRotation() + 10)) * 10,
                                                  character.getPosition().y + sin(deg2rad(character.getRotation() + 10)) * 10),
                                     40, character.getRotation() + (num != 1 ? d : (12 / 2.5f * (rand() % 3 - 1))),
                                     world, characters, Elements));
        timeShot = time;
    };

    using InputData = std::tuple<sf::SoundBuffer*, int, int>;
    std::map<Weapon, InputData> inputDataMap { { Weapon::Pistol, { &sounds.Sgun, 11, 24 } },
                                               { Weapon::Shotgun, { &sounds.Sshotgun, 7, 24 } },
                                               { Weapon::Uzi, { &sounds.Suzi, 29, 9 } },
                                               { Weapon::MG, { &sounds.Smg, 29, 5 } } };    

    if(reloadTime>0)
    {
        reloadTime--;
    }
    else if(timeShot>0)
    {
        timeShot--;
    }
    else
    {
        ammo++;
        createBullet(std::get<0>(inputDataMap[weapon]),
                     std::get<1>(inputDataMap[weapon]),
                     std::get<2>(inputDataMap[weapon]));
    }
}
