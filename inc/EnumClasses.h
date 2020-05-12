#pragma once

enum class Weapon
{
    Pistol,
    Shotgun,
    Uzi,
    MG
};

enum class State 
{
    MainMenu,
    Settings,
    Game,
    ReloadGame
};

enum class GameEngineState
{
	Game,
	Pause,
	DeadPlayer,
	EndLevel,
    MainMenu
};

enum class MenuState 
{
    StartGame,
    LoadGame,
    Settings,
    Menu
};