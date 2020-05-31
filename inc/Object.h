#pragma once

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
    float getSpeed() const { return speed; }

    void setX(float x) { posX+=x; }
    void setY(float x) { posY+=x; }
};