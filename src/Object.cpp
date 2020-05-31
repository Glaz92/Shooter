#include "Object.h"

Object::Object(float x, float y, float r, float s)
    : posX(x), posY(y), rot(r), speed(s), frame(0) {}
Object::~Object()
{}