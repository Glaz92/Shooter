#pragma once

#include "Textures.h"

class Item
{
private:
	Textures & textures;
	sf::Sprite item;

	sf::Vector2f position;

	bool isExist;

	int type; /*
				0 - medicine
				1 - pistol ammo
				2 - shotgun ammo
				3 - uzi ammo
				4 - mg ammo
			  */

public:
	Item(Textures & _textures, sf::Vector2f _position, sf::IntRect rect);
	~Item(void);

public:
	bool ifExist() { return isExist; }
	int getType() { return type; }

	void take() { isExist = false; }

	void setPosition(sf::Vector2f pos) { position = pos; }
	void setRect(sf::IntRect rect);

	void draw();

	sf::Vector2f getPosition() { return position; }

	std::string getString();
};

