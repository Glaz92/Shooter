#include "Element.h"
#include "Window.h"
#include <sstream>
#include <map>

Element::Element(std::string fileName, int t, sf::Vector2f pos, int r, CollisionType colT, Textures & texture, sf::IntRect intR, b2World & world)
    : textureFileName(fileName), type(static_cast<ElementType>(t)), position(pos), rot(r), collisionType(colT), intRect(intR), textures(texture)
{
    switch(type)
    {
    case ElementType::BackSmall:
        obj.setTexture(*textures.back32[textureFileName]);
        break;
    case ElementType::MidSmall:
        obj.setTexture(*textures.mid32[textureFileName]);
        break;
    case ElementType::TopSmall:
        obj.setTexture(*textures.top32[textureFileName]);
        break;
    case ElementType::BackBig:
        obj.setTexture(*textures.back64[textureFileName]);
        break;
    case ElementType::MidBig:
        obj.setTexture(*textures.mid64[textureFileName]);
        break;
    case ElementType::TopBig:
        obj.setTexture(*textures.top64[textureFileName]);
        break;
    }

    obj.setTextureRect(intRect);

    float dimBody = 1.0f, wBody = 36.0f, wABody = 24.0f;

    if(type == ElementType::BackSmall || type == ElementType::MidSmall || type == ElementType::TopSmall)
    {
        obj.setOrigin(16,16);
        dimBody = 0.5f;
    }
    else
    {
        wBody = 160.0f; wABody = 120.0f;
        obj.setOrigin(32,32);
    }

    obj.setRotation(rot);
    obj.setPosition(position);

    b2BodyDef bodyDef;
    switch(collisionType)
    {
    case CollisionType::Static:
        bodyDef.type = b2_staticBody; 
        break;
    case CollisionType::Dynamic:
        bodyDef.type = b2_dynamicBody; 
        break;
    case CollisionType::Non:
        break;
    }

    bodyDef.position.Set( pos.x/64 , pos.y/64 ); 
    bodyDef.angularDamping = wABody;
    bodyDef.linearDamping = wBody; 
    bodyDef.angle = deg2rad(rot);

    if(collisionType != CollisionType::Non)
    {
        body = world.CreateBody(&bodyDef);

        b2PolygonShape bodyShape; 
        bodyShape.SetAsBox( dimBody / 2, dimBody / 2 );

        body->CreateFixture(&bodyShape,1.0f);
    }
}

Element::~Element()
{
}

void Element::draw()
{
    if(collisionType != CollisionType::Non)
    {
        obj.setPosition(body->GetPosition().x*64,body->GetPosition().y*64);
        obj.setRotation(rad2deg(body->GetAngle()));
    }

    GetWindow().draw(&obj);
}

void Element::draw(sf::RenderTexture & Texture)
{
    Texture.draw(obj);
}

void Element::setAll(std::string fileName, int t, sf::Vector2f pos, int r, CollisionType colT, sf::IntRect intR)
{
    textureFileName = fileName;
    type = static_cast<ElementType>(t);
    position = pos;
    rot = r;
    collisionType = colT;
    intRect = intR;

    struct ObjOriginDefault { int value = 32; };
    std::map<ElementType, ObjOriginDefault> objOrigin { { ElementType::BackSmall, ObjOriginDefault { 16 } },
                                                        { ElementType::MidSmall, ObjOriginDefault { 16 } },
                                                        { ElementType::TopSmall, ObjOriginDefault { 16 } } };

    obj.setOrigin(objOrigin[type].value,
                  objOrigin[type].value);

    using TextureMap = std::map<std::string, std::unique_ptr<sf::Texture>>*;
    std::map<ElementType, TextureMap> textureMap { { ElementType::BackSmall, &textures.back32},
                                                    { ElementType::MidSmall, &textures.mid32},
                                                    { ElementType::TopSmall, &textures.top32},
                                                    { ElementType::BackBig, &textures.back64},
                                                    { ElementType::MidBig, &textures.mid64},
                                                    { ElementType::TopBig, &textures.top64} };

    obj.setTexture(*(*textureMap[type])[textureFileName].get());

    obj.setTextureRect(intRect);
    obj.setRotation(0);
}

std::string Element::getString()
{
    std::ostringstream ss;
    ss.str("");

    ss << textureFileName << " " <<  static_cast<int>(type) << " " << position.x << " " << position.y << " " << rot <<
          " " << static_cast<int>(collisionType) << " " << intRect.left << " " << intRect.top << " " << intRect.width <<
          " " << intRect.height << std::endl;

    return ss.str();
}