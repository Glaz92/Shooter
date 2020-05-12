#pragma once
#include <SFML/Audio.hpp>

struct Sounds
{
public:
    sf::SoundBuffer Sgun;            
    sf::SoundBuffer Sshotgun;        
    sf::SoundBuffer Suzi;        
    sf::SoundBuffer Smg;        
    sf::SoundBuffer Sfoot;

public:
    Sounds();
    ~Sounds();
};