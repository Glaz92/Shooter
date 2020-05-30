#include "Bullet.h"
#include "Window.h"

Bullet::Bullet(sf::Vector2f _position, int _strenght, float _rot, b2World & _world, std::vector<Character> & _characters, std::vector<Element> & _objects)
    : position(_position), strenght(_strenght), rot(_rot), bullet(sf::Vector2f(15,4)), lifeTime(0), speed(100), world(_world),
    characters(_characters), objects(_objects)
{
    bullet.setFillColor(sf::Color(200,200,200));
    bullet.setOrigin(0,2);
    bullet.setPosition(position.x, position.y);

    bullet.setRotation(rot);

    minX = abs(cos(deg2rad(rot))*10);
    minY = abs(sin(deg2rad(rot))*10);
}


Bullet::~Bullet(void)
{

}

void Bullet::draw()
{
    if(lifeTime > MAX_BULLET_LIFETIME)
        return;
    
    GetWindow().draw(&bullet);
}

void Bullet::logic(std::vector<BloodAnimation> & blood, Player & player)
{
    if(lifeTime > MAX_BULLET_LIFETIME) return;
    lifeTime++;
    position.x += cos(deg2rad(rot))*40;
    position.y += sin(deg2rad(rot))*40;

    for(auto & object : objects)
    {
        if(object.getColType() != CollisionType::Non)
        {
            switch(object.getType())
            {
            case 232:
                if(abs(object.getPosition().x - position.x)  <23 && abs(object.getPosition().y - position.y) < 23)
                {
                    lifeTime = 700;
                    position.x = -200;
                    position.y = -200;
                }
                break;
            case 264:
                if(abs(object.getPosition().x - position.x) < 45 && abs(object.getPosition().y - position.y) < 45)
                {
                    lifeTime = 700;
                    position.x = -200;
                    position.y = -200;
                }
                break;
            }
        }
    }

    for(auto & character : characters)
    { 
        if(abs(character.getPosition().x - position.x) < 350 && abs(character.getPosition().y - position.y) < 350 && !character.ifDead())
        {
            character.setAlarm(600);
            if(abs(character.getPosition().x - position.x) < 35 && abs(character.getPosition().y - position.y) < 35 && !character.ifDead())
            {
                blood.push_back(BloodAnimation(position.x, position.y, bullet.getRotation()));
                character.changeLife(-strenght);
                lifeTime = 700;
                if(character.ifDead())
                    character.setRot(bullet.getRotation());
            }
        }
    }
    
    if(abs(player.getPosition().x-position.x)<30 && abs(player.getPosition().y-position.y)<30)
    {
        blood.push_back(BloodAnimation(position.x,position.y,bullet.getRotation())); 
        player.changeLife(-strenght);
        lifeTime = 700;; 
    }

    bullet.setPosition(position);
}

bool Bullet::isPointAvaible(float x, float y)
{
    lifeTime++;
    position.x += cos(deg2rad(rot)) * 40;
    position.y += sin(deg2rad(rot)) * 40;

    auto checkPoint = [&] (auto & object, int comparator)
    {
        comparator -= 200;
        if(object.getColType() != CollisionType::Non &&
           abs(object.getPosition().x - position.x) < comparator && abs(object.getPosition().y - position.y) < comparator)
        {
            lifeTime = 700;
            position.x = -200;
            position.y = -200;
        }
    };

    for(auto & object : objects) checkPoint(object, object.getType());

    if(abs(x-position.x) < 23 && abs(y-position.y) < 23 && lifeTime < 660)
    {
        lifeTime = 700;
        position.x = -200;
        position.y = -200;
        return true;
    }

    return false;
}
