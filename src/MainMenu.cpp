#include "MainMenu.h"
#include "Window.h"
#include "GameEngine.h"
#include <SFML/Audio.hpp>
#include <fstream>
#include <ios>

sf::Vector2f posButton(100,400);

MainMenu::MainMenu(std::shared_ptr<GameEngine> & _game)
    :    state(MenuState::Menu), game(_game),
    startGame(sf::Vector2f(posButton.x,posButton.y),"New Game",sf::Vector2f(300,45),3,20),
    loadGame(sf::Vector2f(posButton.x,posButton.y+50),"Load Game",sf::Vector2f(300,45),3,20),
    settings(sf::Vector2f(posButton.x,posButton.y+100),"Settings",sf::Vector2f(300,45),3,20),
    exitGame(sf::Vector2f(posButton.x,posButton.y+150),"Quit Game",sf::Vector2f(300,45),3,20),
    resolution(sf::Vector2f(posButton.x+500,posButton.y-30),"Resolution:\t\t1366 x 768 x 32",sf::Vector2f(380,45),3,20,sf::Color::White,sf::Color(14,14,14)),
    volume(sf::Vector2f(posButton.x+500,posButton.y+15),"Volume:\t\t\t100%",sf::Vector2f(380,45),3,20,sf::Color::White,sf::Color(14,14,14)),
    fullscreen(sf::Vector2f(posButton.x+500,posButton.y+60),"Fullscreen:\t\ton",sf::Vector2f(380,45),3,20,sf::Color::White,sf::Color(14,14,14)),
    saveSettings(sf::Vector2f(posButton.x+500,posButton.y+160),"Save",sf::Vector2f(150,45),3,20,sf::Color::White,sf::Color(14,14,14)),
    playerName(sf::Vector2f(200,30),sf::Vector2f(posButton.x+400,posButton.y+150),true,false),
    playersList(sf::Vector2f(300,150),sf::Vector2f(posButton.x+400,posButton.y-15)),
    start(sf::Vector2f(posButton.x+610,posButton.y+150),"Load",sf::Vector2f(90,30),3,15),
    deleteGame(sf::Vector2f(posButton.x+610,posButton.y+185),"Delete",sf::Vector2f(90,30),3,15),
    video(sf::VideoMode::getFullscreenModes()),
    style(GetWindow().getStyle())
{
    title.setString("Shooter: The Game");
    title.setFont(GetFont(1));
    title.setCharacterSize(65);
    title.setPosition(100,100);
    title.setFillColor(sf::Color::White);

    for(unsigned int i = 0; i < video.size(); i++)
    {
        if(sf::VideoMode::getDesktopMode() == video[i])
        {
            videoMode = i;
            break;
        }
    }

    txt.setString("Put your name:");
    txt.setPosition(posButton.x+400,posButton.y+100);
    txt.setCharacterSize(22);
    txt.setFont(GetFont(2));

    vol = sf::Listener::getGlobalVolume();
    std::ostringstream ss;
    ss.str("");
    ss << "Volume:\t\t\t" << vol << "%";

    volume.setString(ss.str());

    rescaleAll();
}

MainMenu::~MainMenu(void)
{
}

State MainMenu::run()
{
    GetWindow().clear(sf::Color(14,14,14));

    draw();
    return buttons();
}

void MainMenu::draw()
{
    startGame.draw();
    loadGame.draw();
    settings.draw();
    exitGame.draw();
    GetWindow().draw(&title);
    switch(state)
    {
    case MenuState::Menu:
        
        break;
    case MenuState::StartGame:
        playerName.draw();
        start.draw();
        GetWindow().draw(&txt);
        break;
    case MenuState::LoadGame:
        playerName.draw();
        playersList.draw();
        start.draw();
        deleteGame.draw();
        break;
    case MenuState::Settings:
        resolution.draw();
        volume.draw();
        fullscreen.draw();
        saveSettings.draw();
        break;
    }

    aim.draw();
}

void MainMenu::loadPlayerList()
{
    playersList.clear();

    std::fstream load;
    load.open("data\\Configurations\\players.txt");

    std::string tmp;
    while(load >> tmp)
    {
        if(tmp == "player=")
        {
            load >> tmp;
            playersList.addElement(tmp);
        }
    }

    load.close();
}

void MainMenu::deletePlayer()
{
    if(playerName.getString() != "")
    {
        std::fstream load;
        load.open("data\\Configurations\\players.txt");

        std::vector<std::string> tmpString;
        std::ostringstream ss;
        std::string tmpS;

        while(load >> tmpS)
        {
            ss.str("");
            if(tmpS == "player=")
            {
                ss << tmpS << " "; load >> tmpS; 
                if(tmpS == playersList.getSelect())
                {
                    continue;
                }
                ss << tmpS << " "; load >> tmpS;
                if(tmpS == "level=")
                {
                    ss << tmpS << " "; load >> tmpS; ss << tmpS;
                    tmpString.push_back(ss.str());
                }
            }
        }

        load.close();
        load.open("data\\Configurations\\players.txt", std::ios::out);
        for(const auto & str : tmpString)
        {
            load << str << std::endl;
        }
        load.close();

        loadPlayerList();
    }
}

void MainMenu::settingsButtonIsClicked()
{
    for(unsigned int i = 0; i < video.size(); i++)
    {
        if(sf::VideoMode::getDesktopMode() == video[i])
        {
            videoMode = i;
            break;
        }
    }

    state = MenuState::Settings;

    std::ostringstream ss;
    ss.str("");
    ss << "Resolution:\t\t" << video[videoMode].width << " x " << video[videoMode].height << " x " << video[videoMode].bitsPerPixel;

    resolution.setString(ss.str());
    newstyle = style;

    fullscreen.setString(style == sf::Style::Fullscreen ?
                         "Fullscreen:\t\ton" :
                         "Fullscreen:\t\toff");
}

void MainMenu::mainMenuBasicButtons()
{
    auto playerNameAndState = [&](auto str, auto _state, auto input)
    {
        start.setString(str);

        state = _state;

        playerName.setAcvite(false);
        playerName.setInput(input);
        playerName.setString("");
    };

    playersList.isClick();

    if(startGame.isClick())
    {
        playerNameAndState("Start", MenuState::StartGame, true);
    }
    if(loadGame.isClick())
    {
        playerNameAndState("Load", MenuState::LoadGame, false);
        loadPlayerList();
    }
    if(settings.isClick())
    {
        settingsButtonIsClicked();
    }
    if(exitGame.isClick())
    {
        GetWindow().close();
    }
}

bool MainMenu::startOrLoadGame()
{
    auto runGame = [&]()
    {
        if(start.isClick())
        {
            if(playerName.getString() != "")
            {
                game = std::make_shared<GameEngine>(playerName.getString());
                return true;
            }
        }

        return false;
    };

    if(state == MenuState::LoadGame)
    {
        playerName.setString(playersList.getSelect());
        if(deleteGame.isClick())
        {
            deletePlayer();
        }
    }

    return (state == MenuState::LoadGame || state == MenuState::StartGame) ? runGame() : false;
}

void MainMenu::saveSettingsToFile()
{
    GetWindow().setRescale(video[videoMode], newstyle);
    style = newstyle;
    
    std::string fullScreen = newstyle == sf::Style::Fullscreen ? "true" : "false";

    std::fstream conf;
    conf.open("data\\Configurations\\conf.txt",std::ios::out);

    conf << "width= " << video[videoMode].width << "\n"
         << "height= " << video[videoMode].height << "\n"
         << "bitsPerPixel= " << video[videoMode].bitsPerPixel << "\n"
         << "volume= " << vol << "\n"
         << "fullScreen= " << fullScreen << std::endl;

    sf::Listener::setGlobalVolume(vol);

    conf.close();

    rescaleAll();
}

void MainMenu::volumeSeetings()
{
    auto volumePressed = [&](bool increase)
    {
        if(increase ? vol < 100 : vol > 0)
        {
            vol += increase ? 1 : -1;
            std::ostringstream ss;
            ss.str("");
            ss << "Volume:\t\t\t" << vol << "%";

            volume.setString(ss.str());
        }
    };

    if(volume.isPressed())
    {
        volumePressed(true);
    }
    if(volume.isPressedRight())
    {
        volumePressed(false);
    }
}

void MainMenu::fullscreenSettings()
{
    if(fullscreen.isClick() || fullscreen.isClickRight())
    {
        fullscreen.setString(newstyle == sf::Style::Fullscreen ?
                             "Fullscreen:\t\toff" :
                             "Fullscreen:\t\ton");
        
        newstyle = newstyle == sf::Style::Fullscreen ?
                   sf::Style::Default :
                   sf::Style::Fullscreen;
    }
}

void MainMenu::resolutionSettings()
{
    auto setResolutionString = [&]()
    {
        std::ostringstream ss;
        ss.str("");
        ss << "Resolution:\t\t" << video[videoMode].width << " x " << video[videoMode].height << " x " << video[videoMode].bitsPerPixel;

        resolution.setString(ss.str());
    };

    if(resolution.isClickRight())
    {
        videoMode = videoMode < static_cast<int>(video.size()) - 1 ? videoMode + 1 : 0;
        setResolutionString();
    }
    if(resolution.isClick())
    {
        videoMode = videoMode > 0 ? videoMode - 1 : video.size() - 1;
        setResolutionString();
    }
}

void MainMenu::settingsMenu()
{
    resolutionSettings();
    volumeSeetings();
    fullscreenSettings();

    if(saveSettings.isClick())
    {
        saveSettingsToFile();
    }
}

State MainMenu::buttons()
{
    mainMenuBasicButtons();

    if(state == MenuState::Settings)
    {
        settingsMenu();
    }

    return startOrLoadGame() ? State::Game : State::MainMenu;
}

void MainMenu::rescaleAll()
{
    startGame.rescale(GetWindow().getRescale());
    loadGame.rescale(GetWindow().getRescale());
    settings.rescale(GetWindow().getRescale());
    exitGame.rescale(GetWindow().getRescale());

    resolution.rescale(GetWindow().getRescale());
    volume.rescale(GetWindow().getRescale());
    fullscreen.rescale(GetWindow().getRescale());
    saveSettings.rescale(GetWindow().getRescale());

    deleteGame.rescale(GetWindow().getRescale());

    title.setCharacterSize(title.getCharacterSize() * GetWindow().getRescale());
    title.setPosition(title.getPosition().x * GetWindow().getRescale(), title.getPosition().y * GetWindow().getRescale());

    playerName.rescale(GetWindow().getRescale());
    playersList.rescale(GetWindow().getRescale());

    start.rescale(GetWindow().getRescale());
}

