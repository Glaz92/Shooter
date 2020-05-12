#include "MapLoader.h"
#include <sstream>
#include <vector>
#include "Element.h"

void MapLoader::loadFromFile(const std::string playerName, std::shared_ptr<Player> & player, b2World & world, Map & map, std::vector<Character> & characters, Textures & textures)
{
    int lvlNumber = 1;

    if(!playerExist(playerName, lvlNumber))
        createNewPlayer(playerName);

    std::string fileName = getFileName(lvlNumber);

    loadLevelFromFile(fileName, player, world, map, characters, textures);
    setBackgroundTexture(map);
}

bool MapLoader::playerExist(const std::string & playerName, int & lvlNumber)
{
    load.open("data\\Configurations\\players.txt");

    std::string tmp;
    bool exist = false;

    while(load >> tmp)
    {
        if(tmp == "player=")
        {
            load >> tmp;
            if(tmp == playerName)
            {
                load >> tmp;
                if(tmp == "level=")
                {
                    load >> lvlNumber;
                    exist = true;
                }
            }
        }
    }

    load.close();

    return exist;
}

void MapLoader::createNewPlayer(const std::string & playerName)
{
    load.open("data\\Configurations\\players.txt");
    load << "player= " << playerName << " level= " << 1 << std::endl;
    load.close();
}

std::string MapLoader::getFileName(const int lvlNumber)
{
    std::ostringstream ss;
    ss.str("");
    ss << "level" << lvlNumber << "=";

    load.open("data\\Configurations\\levels.txt");
    std::string fileName;
    std::string tmp;

    while(load >> tmp)
    {
        if(tmp == ss.str())
        {
            load >> fileName;
        }
    }
    load.close();

    return fileName;
}

void MapLoader::loadLevelFromFile(const std::string fileName, std::shared_ptr<Player> & player, b2World & world, Map & map, std::vector<Character> & characters, Textures & textures)
{
    load.open("data\\Levels\\"+fileName);

    while(load >> typeReadElement)
    {
        readStartEndPoints(player, world, map);
        readObjectElements(world, map, textures);
        readCharacters(world, characters, textures);
    }

    load.close();
}

void MapLoader::readStartEndPoints(std::shared_ptr<Player> & player, b2World & world, Map & map)
{
    float tmpX, tmpY;
    if(typeReadElement == "startPoint=")
    {
        load >> tmpX >> tmpY;
        
        player = std::make_shared<Player>(world, sf::Vector2f(tmpX, tmpY));
    }
    if(typeReadElement == "endPoint=")
    {
        load >> tmpX >> tmpY;

        map.endPoint.x = tmpX;
        map.endPoint.y = tmpY;
    }
}

void MapLoader::readObjectElements(b2World & world, Map & map, Textures & textures)
{
    int typeDim, typeCol;
    float posX, posY, rot;
    int rectLeft, rectTop, rectW, rectH;
    std::string textureFileName;

    if(typeReadElement == "object=")
    {
        load >> textureFileName >> typeDim >> posX >> posY >> rot >> typeCol >> rectLeft >> rectTop >> rectW >> rectH;

        auto insertElement = [&](auto & elements)
        {
            elements.push_back(Element(textureFileName, typeDim,
                                       sf::Vector2f(posX, posY),
                                       rot, typeCol, textures,
                                       sf::IntRect(rectLeft, rectTop, rectW, rectH),
                                       world));
        };

        if(typeDim == 132 || typeDim == 164) insertElement(ElementsTmp);
        if(typeDim == 232 || typeDim == 264) insertElement(map.ElementsMid);
        if(typeDim == 332 || typeDim == 364) insertElement(map.ElementsTop);

    }
}

void MapLoader::readCharacters(b2World & world, std::vector<Character> & characters, Textures & textures)
{
    int ai, anim, animStep;
    std::string tmpString;
    float posX, posY, rot, tmpX, tmpY;
    int rectLeft, rectTop, rectW, rectH;
    std::vector<sf::Vector2f> tmpVectorPoint;
    std::string textureFileName;

    if(typeReadElement == "character=")
    {
        load >> posX >> posY >> rot >> textureFileName >> rectLeft >> rectTop >> rectW >> rectH >> anim >> animStep >> ai >> tmpString;
        if(tmpString == "vectorON")
        {
            while(load >> tmpString)
            {
                if(tmpString == "vectorEND")
                    break;
                load >> tmpX >> tmpY;
                tmpVectorPoint.push_back(sf::Vector2f(tmpX,tmpY));
            }
        }

        characters.push_back(Character(world, sf::Vector2f(posX, posY),
                                       rot, textures, textureFileName,
                                       sf::IntRect(rectLeft, rectTop, rectW, rectH),
                                       anim, animStep, tmpVectorPoint));
    }
}

void MapLoader::setBackgroundTexture(Map & map)
{
    GetWindow().getBackground().clear(sf::Color::Black);

    for(auto & element : ElementsTmp)
    {
        element.draw(GetWindow().getBackground());
    }

    GetWindow().getBackground().display();

    map.backgroundSprite.setTexture(GetWindow().getBackground().getTexture());    
}