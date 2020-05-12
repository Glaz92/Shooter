#include "Player.h"


Player::Player(b2World & world, sf::Vector2f pos)
	: position(pos), speed(8), life(200)
{
	texture.loadFromFile("data\\Textures\\characters\\player.png");
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody; 
	bodyDef.position.Set( pos.x/64, pos.y/64 );
	bodyDef.angularDamping = 2.0f;
	bodyDef.linearDamping = 120.0f; 

	body = world.CreateBody(&bodyDef);

	b2CircleShape bodyShape;
	bodyShape.m_radius = 0.3f;
//	c.m_p.Set( 0.15, 0.15 );
//	b2PolygonShape bodyShape; 
 //   bodyShape.SetAsBox( 0.625f / 2, 0.625f / 2 );

	body->CreateFixture(&bodyShape,1.0f);

	character.setTexture(texture);
	character.setTextureRect(sf::IntRect(64,0,64,64));
	character.setOrigin(32,32);
	character.setPosition(pos);

}


Player::~Player(void)
{
}

void Player::draw(sf::View & view)
{
	position.x = body->GetPosition().x*64;
	position.y = body->GetPosition().y*64;

	character.setPosition(position);

	GetWindow().draw(&character);

	view.setCenter(character.getPosition());
}

void Player::control()
{

	character.setRotation(-atan2(float(GetWindow().getMousePosition().x-float(GetWindow().getSize().x)/2),
						  float(GetWindow().getMousePosition().y-float(GetWindow().getSize().y)/2))*180/3.1415f+90);

	speed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 16 : 8;

	if( !(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		  sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
		body->SetLinearVelocity((b2Vec2(0.0f, 0.0f)));

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{ 
		body->SetLinearVelocity((b2Vec2(body->GetLinearVelocity().x, -speed)));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		body->SetLinearVelocity((b2Vec2(body->GetLinearVelocity().x, speed)));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		body->SetLinearVelocity((b2Vec2(-speed, body->GetLinearVelocity().y)));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		body->SetLinearVelocity((b2Vec2(speed, body->GetLinearVelocity().y)));
	}
}

