#include "StaticElements.h"

sf::RenderTexture StaticElements::background;
sf::RenderTexture StaticElements::boxRT;

float StaticElements::rescale = 1;
float StaticElements::rescale_t = 1;

StaticElements::StaticElements(void)
{
}


StaticElements::~StaticElements(void)
{
}

void StaticElements::setRescale(sf::VideoMode &  video)
{
    rescale = (float(video.height)/1080.f)/(sf::VideoMode::getDesktopMode().height/1080.f);
    rescale_t = video.height/1080.f;
}

void StaticElements::initSetScale(sf::VideoMode &  video)
{
    rescale = (float(video.height)/1080.f);
    rescale_t = video.height/1080.f;
}