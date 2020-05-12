#include "Character.h"
#include "Window.h"
#include <sstream>

Csounds sounds;

Character::Character(b2World & _world, sf::Vector2f _position, float _rot, Textures & _textures, std::string fileName, sf::IntRect _rect, bool _anim, int _animStep, AItype _ai, std::vector<sf::Vector2f> _points)
	: position(_position), rot(_rot), textures(_textures), textureFileName(fileName), anim(_anim), point(0), world(_world),
	animStep(_animStep), ai(_ai), points(_points), rect(_rect), alarm(0), waitTime(rand()%300), speed(6), down(false), dead(false),
/*	vis(sf::Vector2f(10,10)),*/ life(50), ID(rand()%2323525), timeShot(0), reloadTime(0), ammo(0)
{
	for(int i=0;i<textures.Scharacters.size();i++)
	{
		if(textures.Scharacters[i] == textureFileName)
		{ 
			character.setTexture(*textures.characters[i]);
		}
	}

	character.setTextureRect(rect);
	character.setOrigin(32,32);
	character.setRotation(rot);
	character.setPosition(position);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody; 
	bodyDef.position.Set( position.x/64, position.y/64 );
	bodyDef.angularDamping = 2.0f;
	bodyDef.linearDamping = 120.0f; 

	body = world.CreateBody(&bodyDef);

/*	bodyDef.type = b2_dynamicBody; 
	bodyDef.position.Set( position.x/64, position.y/64 );
	bodyDef.angularDamping = 10.00f;
	bodyDef.linearDamping = 20.000f; 
	
	bodyDef.bullet = true;
	vision = world.CreateBody(&bodyDef);*/
		 
	b2CircleShape bodyShape;
	bodyShape.m_radius = 0.3;

	body->CreateFixture(&bodyShape,1.0f);

/*	bodyShape.m_radius = 0.0003;
	vision->CreateFixture(&bodyShape,1.0f);*/
}

Character::~Character(void)
{
}

void Character::draw()
{
	if(!dead)
	{
		position = sf::Vector2f(body->GetPosition().x*64,body->GetPosition().y*64);
		character.setPosition(position);
//	vis.setPosition(vision->GetPosition().x*64,vision->GetPosition().y*64);
		character.setRotation(rot);
	}
	sf::Listener::setPosition(GetWindow().getViewCenter().x, GetWindow().getViewCenter().y,0);

	GetWindow().draw(&character);  
//	Window.draw(vis);
}

void Character::setAll(sf::Vector2f _position, float _rot, std::string fileName, sf::IntRect _rect, bool _anim, int _animStep, AItype _ai, std::vector<sf::Vector2f> _points)
{
	position = _position;
	rot  = _rot; 
	textureFileName = fileName; 
	anim = _anim;
	animStep = _animStep;
	ai = _ai;
	points = _points;
	rect = _rect;

	for(int i=0;i<textures.Scharacters.size();i++)
	{
		if(textures.Scharacters[i] == textureFileName)
		{ 
			character.setTexture(*textures.characters[i]);
		}
	}

	character.setTextureRect(rect);
}

std::string Character::getString()
{
	std::ostringstream ss;
	ss.str("");

	ss << position.x << " " << position.y << " " << rot << " " << textureFileName << " " << rect.left << " " << rect.top << " " <<
		rect.width << " " << rect.height << " " << anim << " " << animStep << " " << ai << " ";
	if(points.size()>0)
	{
		ss << "vectorON" << std::endl;
		for(int i=0;i<points.size();i++)
		{
			ss << "Point= " << points[i].x << " " << points[i].y << std::endl;
		}
		ss << "vectorEND" << std::endl;
	}
	else
		ss << "vectorOFF" << std::endl;


	return ss.str();
	//sf::Vector2f _position, float _rot, Textures & _textures, string fileName, 
	//sf::IntRect _rect, bool _anim, int _animStep, AItype _ai, vector<sf::Vector2f> _points
}

void Character::behavior(Player & player, std::vector<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements)
{ 
	waitTime--;
	if(alarm == 0)
	{

		if(isPointAvaible(player.getPosition().x,player.getPosition().y, characters, Elements))
		{
			float tmp = -atan2(float(player.getPosition().x-character.getPosition().x),float(player.getPosition().y-character.getPosition().y))*180/3.1415f+90;
			if(character.getRotation()>tmp-80 && character.getRotation()<tmp+80)
			{
				alarm = 100 + rand()%200;
		 		tmpPoints.push_back(player.getPosition());
			}
		}
		if(tmpPoints.size()>0)
		{
			if(abs(character.getPosition().x-tmpPoints[tmpPoints.size()-1].x)<15 && abs(character.getPosition().y-tmpPoints[tmpPoints.size()-1].y)<15)
			{
				tmpPoints.pop_back();
			}
			else
			{
				rot = -atan2(float(tmpPoints[tmpPoints.size()-1].x-character.getPosition().x),float(tmpPoints[tmpPoints.size()-1].y-character.getPosition().y))*180/3.1415f+90;
				body->SetLinearVelocity(b2Vec2(cos(deg2rad(rot))*speed,sin(deg2rad(rot))*speed)); 
			}
		}

		if(points.size() == 0)
		{
			if(abs(character.getPosition().x-position.x)<15 && abs(character.getPosition().y-position.y)<15)
			{
				if(waitTime<10)
				{
					rot+= (rand()%4-2)*70;
					waitTime=60+rand()%500;
				}
			}
			else
			{
				rot = -atan2(float(position.x-character.getPosition().x),float(position.y-character.getPosition().y))*180/3.1415f+90;
				body->SetLinearVelocity(b2Vec2(cos(deg2rad(rot))*speed,sin(deg2rad(rot))*speed));
			}
		}
		else if(tmpPoints.size() == 0)
		{ 
			if(abs(character.getPosition().x-points[point].x)<15 && abs(character.getPosition().y-points[point].y)<15)
			{ 
			//	if(waitTime<10)
			//	{ 
				//	rot+= (rand()%4-2)*70;
				//	waitTime=60+rand()%500;

				if(down)
				{ 
					point--;
					if(point == -1)
					{
						point++;
						down = false;
					}
				}
				else
				{
					point++;
					if(point == points.size())
					{ 
						point--;
						down = true;
					}
				}
			//	}
			}
			else
			{
				rot = -atan2(float(points[point].x-character.getPosition().x),float(points[point].y-character.getPosition().y))*180/3.1415f+90;
				body->SetLinearVelocity(b2Vec2(cos(deg2rad(rot))*speed,sin(deg2rad(rot))*speed));
			}
		}
	}
	else // if alarm > 0
	{
		rot = -atan2(float(player.getPosition().x-character.getPosition().x),float(player.getPosition().y-character.getPosition().y))*180/3.1415f+90;
		if(abs(player.getPosition().x-character.getPosition().x)<150 && abs(player.getPosition().x-character.getPosition().x)<150 && isPointAvaible(player.getPosition().x,player.getPosition().y, characters, Elements))
		{
			if(isPointAvaible(player.getPosition().x,player.getPosition().y, characters, Elements))
				shot(bullets,characters,Elements);
			alarm = 450;
		}
		else
		{ 
			if(abs(player.getPosition().x-character.getPosition().x)<550 && abs(player.getPosition().x-character.getPosition().x)<550)
				if(isPointAvaible(player.getPosition().x,player.getPosition().y, characters, Elements))
					shot(bullets,characters,Elements);
			if(tmpPoints.size()>0 && abs(character.getPosition().x-tmpPoints[tmpPoints.size()-1].x)<15 && abs(character.getPosition().y-tmpPoints[tmpPoints.size()-1].y)<15)
			{
				if(isPointAvaible(player.getPosition().x,player.getPosition().y, characters, Elements))
				{
					tmpPoints.push_back(player.getPosition());
				}
			}
			else
			{
				if(tmpPoints.size()==0)
					tmpPoints.push_back(character.getPosition());
				if(isPointAvaible(player.getPosition().x,player.getPosition().y, characters, Elements))
				{
					alarm = 450;
					tmpPoints[tmpPoints.size()-1] = character.getPosition();
					tmpPoints.push_back(player.getPosition());
					rot = -atan2(float(tmpPoints[tmpPoints.size()-1].x-character.getPosition().x),float(tmpPoints[tmpPoints.size()-1].y-character.getPosition().y))*180/3.1415f+90;
					body->SetLinearVelocity(b2Vec2(cos(deg2rad(rot))*speed,sin(deg2rad(rot))*speed)); 
				}
				else
				{
					if(tmpPoints.size()>0)
					{
						rot = -atan2(float(tmpPoints[tmpPoints.size()-1].x-character.getPosition().x),float(tmpPoints[tmpPoints.size()-1].y-character.getPosition().y))*180/3.1415f+90;
						body->SetLinearVelocity(b2Vec2(cos(deg2rad(rot))*speed,sin(deg2rad(rot))*speed)); 
					}
				}
			}
		}

		alarm--;

	}


}

bool Character::isPointAvaible(float x, float y, std::vector<Character> & characters, std::vector<Element> & Elements)
{
	float tmpRot = -atan2(float(x-character.getPosition().x),float(y-character.getPosition().y))*180/3.1415f+90;
	Bullet visionTmp(character.getPosition(),0,tmpRot,world,characters,Elements);

	while(visionTmp.getLifeTime()<540)
	{ 
		if(visionTmp.isPointAvaible(x,y))
			return true;
	}

	return false;

	/*

	if(abs(vision->GetLinearVelocity().x) < 10 || abs(vision->GetLinearVelocity().y) < 10)
	{
		if(abs(vision->GetPosition().x-x)<0.6 && abs(vision->GetPosition().y-y)<0.6)
			return true;
		float rotTmp = deg2rad(-atan2(float(x-body->GetPosition().x),float(y-body->GetPosition().y))*180/3.1415f+90);
		vision->SetTransform(b2Vec2(body->GetPosition().x+cos(rotTmp)/4,body->GetPosition().y+sin(rotTmp)/4),0);
		vision->ApplyLinearImpulse(b2Vec2(cos(rotTmp)*100,sin(rotTmp)*100),b2Vec2(x,y),true);// b2Vec2(cos(rotTmp)*100,sin(rotTmp)*100));
	}
	else if(abs(vision->GetPosition().x-x)<0.6 && abs(vision->GetPosition().y-y)<0.6)
		return true;

	return false; */
} 

void Character::shot(std::vector<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements)
{
	sound.setPosition(position.x,position.y,0);
	sound.setRelativeToListener(true);
	if(reloadTime>0)
	{
		reloadTime--;
	}
	else if(timeShot>0)
		timeShot--;
	else
	{
		ammo++;
		switch(int(rect.left/64))
		{
		case 0:
			if(ammo>11)
				reloadTime = 100;
			sound.setBuffer(sounds.Sgun);
			sound.play();
			bullets.push_back(Bullet(sf::Vector2f(character.getPosition().x+cos(deg2rad(character.getRotation()+10))*10,character.getPosition().y+sin(deg2rad(character.getRotation()+10))*10),40,character.getRotation()+12/2.5f*(rand()%3-1), world, characters,Elements));
			timeShot = 24;
			break;
		case 1:
			if(ammo>7)
				reloadTime = 100;
			sound.setBuffer(sounds.Sshotgun);
			sound.play();
			bullets.push_back(Bullet(sf::Vector2f(character.getPosition().x+cos(deg2rad(character.getRotation()+10))*10,character.getPosition().y+sin(deg2rad(character.getRotation()+10))*10),40,character.getRotation()+12/2.5f*(rand()%3-1)+6, world, characters,Elements));
			bullets.push_back(Bullet(sf::Vector2f(character.getPosition().x+cos(deg2rad(character.getRotation()+10))*10,character.getPosition().y+sin(deg2rad(character.getRotation()+10))*10),40,character.getRotation()+12/2.5f*(rand()%3-1)+3, world, characters,Elements));
			bullets.push_back(Bullet(sf::Vector2f(character.getPosition().x+cos(deg2rad(character.getRotation()+10))*10,character.getPosition().y+sin(deg2rad(character.getRotation()+10))*10),40,character.getRotation()+12/2.5f*(rand()%3-1), world, characters,Elements));
			bullets.push_back(Bullet(sf::Vector2f(character.getPosition().x+cos(deg2rad(character.getRotation()+10))*10,character.getPosition().y+sin(deg2rad(character.getRotation()+10))*10),40,character.getRotation()+12/2.5f*(rand()%3-1)-3, world, characters,Elements));
			bullets.push_back(Bullet(sf::Vector2f(character.getPosition().x+cos(deg2rad(character.getRotation()+10))*10,character.getPosition().y+sin(deg2rad(character.getRotation()+10))*10),40,character.getRotation()+12/2.5f*(rand()%3-1)-6, world, characters,Elements));
			timeShot = 24;
			break;
		case 2:
			if(ammo>29)
				reloadTime = 100;
			sound.setBuffer(sounds.Suzi);
			sound.play();
			bullets.push_back(Bullet(sf::Vector2f(character.getPosition().x+cos(deg2rad(character.getRotation()+10))*10,character.getPosition().y+sin(deg2rad(character.getRotation()+10))*10),40,character.getRotation()+12/2.5f*(rand()%3-1), world, characters,Elements));
			timeShot = 9;
			break;
		case 3:
			if(ammo>29)
				reloadTime = 100;
			sound.setBuffer(sounds.Smg);
			sound.play();
			bullets.push_back(Bullet(sf::Vector2f(character.getPosition().x+cos(deg2rad(character.getRotation()+10))*10,character.getPosition().y+sin(deg2rad(character.getRotation()+10))*10),40,character.getRotation()+12/2.5f*(rand()%3-1), world, characters,Elements));
			timeShot = 5;
			break;
		}
	}
}

Csounds::Csounds()
{
//	Sfoot.loadFromFile("data\\sounds\\footstep.wav");
	Sgun.loadFromFile("data\\sounds\\gunfire.wav");
	Sshotgun.loadFromFile("data\\sounds\\shotgun.wav");
	Suzi.loadFromFile("data\\sounds\\gunfire.wav");
	Smg.loadFromFile("data\\sounds\\mg.wav");
}

Csounds::~Csounds()
{

}