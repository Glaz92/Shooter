#pragma once

#include <vector>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class Textures
{
public:
	std::map<std::string, sf::Texture*> top32;
	std::map<std::string, sf::Texture*> top64;
	std::map<std::string, sf::Texture*> mid32;
	std::map<std::string, sf::Texture*> mid64;

	std::map<std::string, sf::Texture*> back32;
	std::map<std::string, sf::Texture*> back64;

	std::map<std::string, sf::Texture*> characters;

public:
	Textures();
	~Textures();

private:
	void FindAndLoad(std::map<std::string, sf::Texture*> & textureList, const char * path, std::string path_);
};

