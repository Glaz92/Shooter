#pragma once

#include <SFML/Graphics.hpp>

class StaticElements
{
public:
	static sf::RenderTexture background;
	static sf::RenderTexture boxRT;

	static float rescale;
	static float rescale_t;

public:
	StaticElements(void);
	~StaticElements(void);

public:
	static void setRescale(sf::VideoMode &  video);
	static void initSetScale(sf::VideoMode &  video);
};

