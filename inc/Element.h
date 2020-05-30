#pragma once

#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <string>
#include "Textures.h"

enum class CollisionType
{
    Non,
    Static,
    Dynamic
};

enum class ElementType
{
    BackBig = 164,
    BackSmall = 132,
    MidBig = 264,
    MidSmall = 232,
    TopBig = 364,
    TopSmall = 332
};
class Element
{
private:
    std::string textureFileName;
    ElementType type;
    sf::Vector2f position;

    float rot;
    CollisionType collisionType;
    sf::IntRect intRect;
    Textures & textures;
    sf::Sprite obj;
    b2Body * body;

public:
    Element(std::string fileName, int t, sf::Vector2f pos, int r, CollisionType colT, Textures & texture, sf::IntRect intR, b2World & world);

    ~Element();

public:
    sf::Vector2f getPosition() { return position; }
    CollisionType getColType() { return collisionType; }
    void setColType(CollisionType t) { collisionType = t; }
    int getType() { return static_cast<int>(type); }
    float getRot() { return rot; }
    std::string getFileName() { return textureFileName; }

    void setPosition(sf::Vector2f pos) { position = pos; obj.setPosition(position); }
    void setRot(float i) { rot = i; obj.setRotation(rot); }
    void rotate(float r) { rot+=r; obj.setRotation(rot); }

    void setAll(std::string fileName, int t, sf::Vector2f pos, int r, CollisionType colT, sf::IntRect intR);
    void draw();
    void draw(sf::RenderTexture & Texture);

    std::string getString();
};

