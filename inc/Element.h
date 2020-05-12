#pragma once

#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <string>
#include "Textures.h"

class Element
{
private:
	std::string textureFileName;
	int type; /*	132 // 164 - back
					232 // 264 - mid
			  		332 // 364 - top  */

	sf::Vector2f position;

	float rot;
	int colType; // 0 - non, 1 - static, 2 - dynamic
	sf::IntRect intRect;
	Textures & textures;
	sf::Sprite obj;
	b2Body * body;

public:
	Element(std::string fileName, int t, sf::Vector2f pos, int r, int colT, Textures & texture, sf::IntRect intR, b2World & world);
//	Object(Object & copy);

	~Element();

public:
	sf::Vector2f getPosition() { return position; }
	int getColType() { return colType; }
	void setColType(int t) { colType = t; }
	int getType() { return type; }
	float getRot() { return rot; }
	std::string getFileName() { return textureFileName; }

	void setPosition(sf::Vector2f pos) { position = pos; obj.setPosition(position); }
	void setRot(float i) { rot = i; obj.setRotation(rot); }
	void rotate(float r) { rot+=r; obj.setRotation(rot); }

	void setAll(std::string fileName, int t, sf::Vector2f pos, int r, int colT, sf::IntRect intR);
	void draw();
	void draw(sf::RenderTexture & Texture);

	std::string getString();

//	Element & operator=(const Element & tmp) { return *this = tmp; }
};

