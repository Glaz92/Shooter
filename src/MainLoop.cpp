#include "MainLoop.h"
#include "Window.h"

MainLoop::MainLoop()
	: state(State::MainMenu), menu(game)
{
}

MainLoop::~MainLoop()
{
}

MainLoop & MainLoop::get()
{
	static MainLoop mainLoop;

	return mainLoop;
}

GameState * MainLoop::getGameState()
{
	switch(state)
	{
	case State::Game:
		return game.get();
	case State::ReloadGame:
		game = std::make_shared<GameEngine>(game->getName());
		return game.get();
	case State::Settings:
	default:
		return &menu;
	}
}

void MainLoop::run()
{
	while(GetWindow().isOpen())
	{
		sf::Event event;
		while(GetWindow().pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				GetWindow().close();
		}

		GetWindow().clear(sf::Color::Black);

		state = getGameState()->run();

		GetWindow().display();
	}
}