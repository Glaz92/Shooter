#pragma once

#include "Character.h"
#include "BloodAnimation.h"
#include "Player.h"
#include "Element.h"

class Character;

constexpr int MAX_BULLET_LIFETIME = 650;

class Bullet
{
private:
	sf::Vector2f position;
	int strenght;
	float rot;
	sf::RectangleShape bullet;
	int lifeTime;
	float speed;
	b2World & world;
	std::vector<Character> & characters;
	std::vector<Element> & objects;
	float minX;
	float minY;

public:
	Bullet(sf::Vector2f _position, int _strenght, float _rot, b2World & _world, std::vector<Character> & _characters, std::vector<Element> & _objects);
	~Bullet();

public:
	void draw();
	void logic(std::vector<BloodAnimation> & blood, Player & player);
	int getLifeTime() { return lifeTime; }

	bool isPointAvaible(float x, float y);

private:
	sf::Vector2f getPosition() { return position; }
	int getStrenght() { return strenght; }
};

