#include "GameMenu.h"
#include "Window.h"

const sf::Vector2f posButton(100,400);

GameMenu::GameMenu()
    : title("Placeholder", GetFont(2), 50 * GetWindow().getRescaleT()),
    stat("Placeholder", GetFont(1), 30 * GetWindow().getRescaleT()),
    shapeTmp(sf::Vector2f(4000, 4000)),
    Bresume(sf::Vector2f(posButton.x, posButton.y), "Resume", sf::Vector2f(300,45), 2, 20),
    BtryAgain(sf::Vector2f(posButton.x, posButton.y), "Try again", sf::Vector2f(300,45), 2, 20),
    BnextLevel(sf::Vector2f(posButton.x, posButton.y), "Next level", sf::Vector2f(300,45), 2, 20),
    BrestartLevel(sf::Vector2f(posButton.x, posButton.y + 50), "Restart level", sf::Vector2f(300,45), 2, 20),
    BmainMenu(sf::Vector2f(posButton.x, posButton.y + 100), "Main menu", sf::Vector2f(300,45), 2, 20),
    BquitGame(sf::Vector2f(posButton.x, posButton.y + 150), "Quit Game", sf::Vector2f(300,45), 2, 20)
{
    shapeTmp.setFillColor(sf::Color(15, 15, 15, 140));
    shapeTmp.setOrigin(2000, 2000);

    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    stat.setOrigin(stat.getGlobalBounds().width / 2, stat.getGlobalBounds().height / 2);
}

GameMenu::~GameMenu()
{

}

GameEngineState GameMenu::pause()
{
    title.setString("Pause");
    shapeTmp.setPosition(GetWindow().getViewCenter());

    title.setPosition(GetWindow().getViewCenter().x, GetWindow().getViewCenter().y - 150 * GetWindow().getRescaleT());
    stat.setPosition(GetWindow().getViewCenter().x,GetWindow().getViewCenter().y - 50 * GetWindow().getRescaleT());

    GetWindow().draw(&shapeTmp);

    GetWindow().draw(&title);
    GetWindow().draw(&stat);

    Bresume.draw();
    BmainMenu.draw();
    BquitGame.draw();

    if(Bresume.isClick())
    {
        return GameEngineState::Game;
    }
    if(BmainMenu.isClick())
    {
        return GameEngineState::MainMenu;
    }
    if(BquitGame.isClick())
    {
        GetWindow().close();
    }

    return GameEngineState::Pause;
}

State GameMenu::deadPlayer()
{
    title.setString("You are dead!");
    shapeTmp.setPosition(GetWindow().getViewCenter());

    title.setPosition(GetWindow().getViewCenter().x, GetWindow().getViewCenter().y - 150 * GetWindow().getRescaleT());
    stat.setPosition(GetWindow().getViewCenter().x,GetWindow().getViewCenter().y - 50 * GetWindow().getRescaleT());

    GetWindow().draw(&shapeTmp);

    GetWindow().draw(&title);
    GetWindow().draw(&stat);

    BtryAgain.draw();
    BmainMenu.draw();
    BquitGame.draw();

    if(BtryAgain.isClick())
    {
        return State::ReloadGame;
    }
    if(BmainMenu.isClick())
    {
        return State::MainMenu;
    }
    if(BquitGame.isClick())
    {
        GetWindow().close();
    }

    return State::Game;
}