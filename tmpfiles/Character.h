#pragma once

#include "Textures.h"
#include "Player.h"
#include "Bullet.h"
#include "Element.h"
#include <SFML/Audio.hpp>

enum AItype { ZOMBIE, EASY, MEDIUM, HARD };

class Bullet;

class Csounds
{
public:
	sf::SoundBuffer Sgun;			
	sf::SoundBuffer Sshotgun;		
	sf::SoundBuffer Suzi;		
	sf::SoundBuffer Smg;		
	sf::SoundBuffer Sfoot;

public:
	Csounds();
	~Csounds();

};

extern Csounds sounds;

class Character
{
private:
	sf::Vector2f position;
	float rot;

	sf::Sound sound;

	int ID;

	int ammo;

	std::string textureFileName;
	Textures & textures;
	sf::IntRect rect;

	bool dead;
	bool anim;
	int animStep;

	AItype ai;

	std::vector<sf::Vector2f> points;
	std::vector<sf::Vector2f> tmpPoints;

	sf::Sprite character;

	b2Body * body;
//	b2Body * vision;
//	sf::RectangleShape vis;

	int waitTime;
	int alarm;		// jezeli 0, to spokojny, jezeli nie widzi gracza, to wartosc spada
					// do czasu uzyskania wartosci 0

	int timeShot;
	int reloadTime;

	float speed;
	int point;
	bool down;

	b2World & world;

	int life;

public:
	Character(b2World & _world, sf::Vector2f _position, float _rot, Textures & _textures, std::string fileName, sf::IntRect _rect, bool _anim, int _animStep, AItype _ai, std::vector<sf::Vector2f> _points);
//	Character(Character & copy);
	~Character(void);

	Character & operator=(const Character & tmp) { return * this; }

public:
	void draw();

	void setPosition(float x, float y) { position.x = x; position.y = y; }
	void setAll(sf::Vector2f _position, float _rot, std::string fileName, sf::IntRect _rect, bool _anim, int _animStep, AItype _ai, std::vector<sf::Vector2f> _points);

	void setRect(sf::IntRect _rect) { rect = _rect; }
	void setAI(AItype _ai) { ai = _ai; }
	void setAnim(bool _anim) { anim = _anim; }
	void setAnimStep(int tmp) { animStep = tmp; }
	void setPoints(std::vector<sf::Vector2f> p) { points = p; }

	void setAlarm(int x) { alarm = x; }

	void rotate(float r) { rot+=r; }

	void setRot(float _rot) { rot = _rot; }
	std::string getString();

	void behavior(Player & player, std::vector<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements);
	void shot(std::vector<Bullet> & bullets, std::vector<Character> & characters, std::vector<Element> & Elements);

	sf::Vector2f getPosition() { return position; }

	void changeLife(int x) { life += x; }
	int getLife() { return life; }  

	int getID() { return ID; }

	void isDead() { world.DestroyBody(body);  dead = true; character.setTextureRect(sf::IntRect(0,64,128,64)); character.setOrigin(64,32); } 
	bool ifDead() { return dead; }

private:
	bool isPointAvaible(float x, float y, std::vector<Character> & characters, std::vector<Element> & Elements);
};

