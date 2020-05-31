#include "BloodAnimation.h"
#include "Window.h"
#include <cmath>

BloodAnimation::BloodAnimation(float xx, float yy, float tmpX)
    : x(xx), y(yy), bloodG(sf::Vector2f(4,4))
{
    bloodG.setFillColor(sf::Color(190,0,0));
    lifetime=450;
    int nB = rand() % 20 + 20;

    for(int i = 0; i < nB; i++)
    {
        BulletObject tmp(xx,yy,tmpX+rand()%30-15,rand()%10+5,rand()%15,0);
        blood.push_back(tmp);
    }
}
BloodAnimation::BloodAnimation(float xx, float yy)
    : x(xx), y(yy), bloodG(sf::Vector2f(4,4))
{
    bloodG.setFillColor(sf::Color(190,0,0));
    lifetime=1600;
    int nB = rand() % 200 + 200;

    for(int i = 0; i < nB; i++)
    {
        BulletObject tmp(xx,yy,rand()%360,rand()%10+5,rand()%15,0);
        blood.push_back(tmp);
    }
}
BloodAnimation::~BloodAnimation()
{}

void BloodAnimation::draw()
{
    for(auto & b : blood)
    {
        if(b.getLifetime()>0)
        {
            b.setX(cos(deg2rad(b.getRot())) * b.getSpeed());
            b.setY(sin(deg2rad(b.getRot())) * b.getSpeed());
            b.setLifetime(-1);
        }
        bloodG.setPosition(b.getX(), b.getY());
        GetWindow().draw(&bloodG);
    }
    lifetime = lifetime != 0 ? lifetime - 1 : 0;
    
    if(lifetime < blood.size())
        blood.pop_back();
}
