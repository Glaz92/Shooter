#include "TxtBox.h"
#include "Window.h"
#include <map>
#include <utility>

TxtBox::TxtBox(sf::Vector2f s, sf::Vector2f pos, bool in, bool onlyNumbers)
    : input(in), box(s), position(pos), size(s), active(false), onlyNum(onlyNumbers)
{
    font.loadFromFile("data/font/calibri.ttf");
    txt.setFont(font);
    txt.setString("");
    txt.setFillColor(sf::Color::Black);
    txt.setCharacterSize(15);

    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::Black);
    box.setFillColor(sf::Color(230, 230, 230));

    box.setPosition(position.x, position.y);
    txt.setPosition(position.x + 5, position.y + 3);
}


TxtBox::~TxtBox()
{
}

void TxtBox::draw()
{
    if(input)
    {
        if(active)
        {
            inputTxt();
            box.setOutlineColor(sf::Color::Red);
        }
        else
        {
            box.setOutlineColor(sf::Color::Black);
        }

        if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
        {
            if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
            {
                box.setOutlineColor(sf::Color(60,120,180));
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    active=true;
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                active=false;
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            active=false;
    }
    else
        box.setOutlineColor(sf::Color::Black);

    txt.setString(ss.str());

    GetWindow().draw(&box);
    GetWindow().draw(&txt);
}

void TxtBox::inputTxt()
{
    using upperLowerLetter = std::pair<char, char>;
    using KeyEnum = sf::Keyboard::Key;
    std::map<KeyEnum, upperLowerLetter> keyMap { { KeyEnum::A, { 'a', 'A' } }, { KeyEnum::B, { 'b', 'B' } }, { KeyEnum::C, { 'c', 'C' } },
                                                 { KeyEnum::D, { 'd', 'D' } }, { KeyEnum::E, { 'e', 'E' } }, { KeyEnum::F, { 'f', 'F' } },
                                                 { KeyEnum::G, { 'g', 'G' } }, { KeyEnum::H, { 'h', 'H' } }, { KeyEnum::I, { 'i', 'I' } },
                                                 { KeyEnum::J, { 'j', 'J' } }, { KeyEnum::K, { 'k', 'K' } }, { KeyEnum::L, { 'l', 'L' } },
                                                 { KeyEnum::M, { 'm', 'M' } }, { KeyEnum::N, { 'n', 'N' } }, { KeyEnum::O, { 'o', 'O' } },
                                                 { KeyEnum::P, { 'p', 'P' } }, { KeyEnum::R, { 'r', 'R' } }, { KeyEnum::S, { 's', 'S' } },
                                                 { KeyEnum::T, { 't', 'T' } }, { KeyEnum::U, { 'u', 'U' } }, { KeyEnum::W, { 'w', 'W' } },
                                                 { KeyEnum::Y, { 'y', 'Y' } }, { KeyEnum::Z, { 'z', 'Z' } }, { KeyEnum::X, { 'a', 'X' } },
                                                 { KeyEnum::Q, { 'q', 'Q' } } };

    for(const auto & key : keyMap)
    {
        if(sf::Keyboard::isKeyPressed(key.first))
        {
            if(sf::Keyboard::isKeyPressed(KeyEnum::LShift) || sf::Keyboard::isKeyPressed(KeyEnum::RShift))
            {
                ss << key.second.second;
            }
            else
            {
                ss << key.second.first;
            }
            
        }
        while(sf::Keyboard::isKeyPressed(key.first));
    }

    if(sf::Keyboard::isKeyPressed(KeyEnum::BackSpace))
    {
        std::string tmpS=ss.str();
        ss.str("");
        ss << tmpS.substr(0, tmpS.length() - 1);
    }
}

void TxtBox::rescale(float x)
{
    x = x > 2 ? 2 : 1;
}