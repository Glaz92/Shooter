#pragma once
#include "GameState.h"
#include "MainMenu.h"
#include "GameEngine.h"
#include "EnumClasses.h"
#include <memory>

class MainLoop
{
private:
    State state;
    MainMenu menu;
    std::shared_ptr<GameEngine> game;

    GameState * getGameState();

private:
    MainLoop();
    ~MainLoop();

public:
    static MainLoop & get();

    void run();
};

constexpr auto GetMainLoop = &MainLoop::get;