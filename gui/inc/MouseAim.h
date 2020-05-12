#pragma once
#include <SFML/Graphics.hpp>

class MouseAim
{
private:
	sf::RectangleShape top;
	sf::RectangleShape bottom;
	sf::RectangleShape left;
	sf::RectangleShape right;

	float delta, deltaTmp;
	sf::Vector2f pos;

public:
	MouseAim(void);
	~MouseAim(void);

public:
	void draw();
	void setDelta(float _delta) { delta = _delta; }

	float getDelta() { return delta; }
	sf::Vector2f getPosition() { return pos; }

};

