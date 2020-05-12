#pragma once

#include "GameState.h"
#include "Button.h"
#include "TxtBox.h"
#include "ListBox.h"
#include "GameEngine.h"
#include "MouseAim.h"
#include "CheckBox.h"
#include "EnumClasses.h"
#include <vector>
#include <memory>

class MainMenu : public GameState
{
private:
	MenuState state;
	std::shared_ptr<GameEngine> & game;

	Button startGame;
	Button loadGame;
	Button settings;
	Button exitGame;

	Button resolution;
	Button volume;
	Button fullscreen;
	Button saveSettings;

	TxtBox playerName;
	ListBox playersList;

	Button start;
	Button deleteGame;

	sf::Text title;
	std::vector<sf::VideoMode> video;
	int videoMode;

	sf::Uint32 style;
	sf::Uint32 newstyle;
	int vol;
	MouseAim aim;
	sf::Text txt;

public:
	MainMenu(std::shared_ptr<GameEngine> & _game); //sf::Uint32 & _style);
	~MainMenu(void);

public:
	void mainLoop();
	State run();

private:
	void draw();
	State buttons();

	void rescaleAll();
};

