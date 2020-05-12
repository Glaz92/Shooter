#pragma once

#include <string>
#include <memory>
#include <fstream>
#include "Player.h"
#include "Character.h"
#include "Map.h"

class MapLoader
{
private:
    std::vector<Element> ElementsTmp;
    std::fstream load;
    std::string typeReadElement;

public:
    void loadFromFile(const std::string playerName, std::shared_ptr<Player> & player, b2World & world, Map & map, std::vector<Character> & characters, Textures & textures);

private:
    bool playerExist(const std::string & playerName, int & lvlNumber);
    void createNewPlayer(const std::string & playerName);
    std::string getFileName(const int lvlNumber);

    void loadLevelFromFile(const std::string fileName, std::shared_ptr<Player> & player, b2World & world, Map & map, std::vector<Character> & characters, Textures & textures);

    void readStartEndPoints(std::shared_ptr<Player> & player, b2World & world, Map & map);
    void readObjectElements(b2World & world, Map & map, Textures & textures);
    void readCharacters(b2World & world, std::vector<Character> & characters, Textures & textures);

    void setBackgroundTexture(Map & map);
};