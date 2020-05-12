#pragma once

#include "EnumClasses.h"

class GameState
{
public:
    virtual State run() = 0;

    GameState();
    virtual ~GameState();
};