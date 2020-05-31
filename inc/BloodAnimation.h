#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "BulletObject.h"

class BloodAnimation
{
private:
    float x;
    float y;
    std::vector<BulletObject> blood;
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