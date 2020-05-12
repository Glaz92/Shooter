#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Object
{
protected:
    float posX;
    float posY;
    float rot;
    float speed;
    int frame;

public:
    Object(float x, float y, float r, float s);
    virtual ~Object();

public:
    float getX() const { return posX; }
    float getY() const { return posY; }
    float getRot() const { return rot; }
    int getFrame(int x) const { return frame/x; }
    float getSpeed() const { return speed; }

    void setX(float x) { posX+=x; }
    void setY(float x) { posY+=x; }
    void changeX(float x) { posX=x; }
    void changeY(float x) { posY=x; }
    void setRot(float x) { rot+=x; }
    void changeRot(float x) { rot=x; }
    void setFrame(int x) { frame+=x; }
    void changeFrame(int x) { frame=x; }
    void changeSpeed(float x) { speed=x; }

};

class bulletObject : public Object // pociski oraz "wzrok"
{
protected:
    float lifetime;
    int power;

public:
    bulletObject(float x, float y, float r, float s, float l, int p);
    ~bulletObject();

public:
    float getLifetime() const { return lifetime; }
    int getPower() const { return power; }

    void setLifetime(float x) { lifetime += x; }
    void changeLifetime(float x) { lifetime = x; }
};

class BloodAnimation
{
private:
    float x;
    float y;
    std::vector<bulletObject> blood;
    unsigned int lifetime;

    sf::RectangleShape bloodG;

public:
    BloodAnimation(float xx, float yy, float tmpX);
    BloodAnimation(float xx, float yy);
    ~BloodAnimation();

public:
    int getLifetime() const { return lifetime; }

    void draw();
};