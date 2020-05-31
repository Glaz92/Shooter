#include "BulletObject.h"

BulletObject::BulletObject(float x, float y, float r, float s, float l, int p)
    : Object(x,y,r,s), lifetime(l), power(p) {}
BulletObject::~BulletObject()
{}