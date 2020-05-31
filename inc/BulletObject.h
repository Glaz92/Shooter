#pragma once

#include "Object.h"

class BulletObject : public Object
{
protected:
    float lifetime;
    int power;

public:
    BulletObject(float x, float y, float r, float s, float l, int p);
    ~BulletObject();

public:
    float getLifetime() const { return lifetime; }
    int getPower() const { return power; }

    void setLifetime(float x) { lifetime += x; }
    void changeLifetime(float x) { lifetime = x; }
};