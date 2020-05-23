#include "Window.h"
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <cmath>

bool Window::instance = false;

Window::Window(sf::VideoMode & video, sf::Uint32 & style)
    : window(video, "Shooter", style), initStyle(style)
{
    font0.loadFromFile("data/font/calibri.ttf");
    font1.loadFromFile("data/font/WC_RoughTrad.otf");
    font2.loadFromFile("data/font/Akashi.ttf");
    font3.loadFromFile("data/font/CodenameCoderFree4F-Bold.ttf");

    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    background.create(8192,8192);

    sf::RectangleShape tmp(sf::Vector2f(45,15));
    tmp.setFillColor(sf::Color(190,0,0,140));
    tmp.setPosition(20,35);
    boxRT.draw(tmp);
    tmp.setSize(sf::Vector2f(15,15));
    tmp.setPosition(35,20);
    boxRT.draw(tmp);
    tmp.setPosition(35,50);
    boxRT.draw(tmp);
    boxRT.display();
}

Window::~Window()
{

}

Window & Window::get()
{
    static Window & win = initialize();

    return win;
}

sf::Font & Window::getFont(int x)
{
    if(x == 1) return get().font0;
    else if(x == 2) return get().font1;
    else if(x == 3) return get().font3;
    return get().font2;
}

void Window::draw(sf::Drawable * object)
{
    window.draw(*object);
}

bool Window::isOpen()
{
    return window.isOpen();
}

void Window::clear(sf::Color color)
{
    window.clear(color);
}

void Window::display()
{
    window.display();
}

void Window::close()
{
    window.close();
}

void Window::setView(sf::View & view)
{
    window.setView(view);
}

void Window::setDefaultView()
{
    window.setView(window.getDefaultView());
}

void Window::setMouseCursorVisible(bool value)
{
    window.setMouseCursorVisible(value);
}

bool Window::pollEvent(sf::Event & event)
{
    return window.pollEvent(event);
}

sf::Vector2i Window::getMousePosition()
{
    return sf::Mouse::getPosition(window);
}

sf::Vector2f Window::getViewCenter()
{
    return window.getView().getCenter();
}

sf::Vector2u Window::getSize()
{
    return window.getSize();
}

sf::View Window::getView()
{
    return window.getView();
}

void Window::loadVideoMode(sf::VideoMode & video, sf::Uint32 & style)
{
    int success=0;
    std::fstream conf;
    conf.open("data\\Configurations\\conf.txt");
    std::string tmpS;
    while(conf >> tmpS)
    {
        if(tmpS=="width=")
        {
            conf >> video.width;
            if(video.width>790 || video.width< 1400)
                success++;
        }
        else if(tmpS=="height=")
        {
            conf >> video.height;
            if(video.height>590 || video.height< 800)
                success++;
        }
        else if(tmpS=="bitsPerPixel=")
        {
            conf >> video.bitsPerPixel;
            if(video.bitsPerPixel>15 || video.bitsPerPixel<=sf::VideoMode::getDesktopMode().bitsPerPixel)
                success++;
        }
        else if(tmpS=="volume=")
        {
            float tmpV;
            conf >> tmpV;
            sf::Listener::setGlobalVolume(tmpV);
        }
        else if(tmpS=="fullScreen=")
        {
            std::string tmp;
            conf >> tmp;
            if(tmp == "true")
                style = sf::Style::Fullscreen;
            else
                style = sf::Style::Default;
        }
    }
    conf.close();
}

Window & Window::initialize()
{
    sf::VideoMode videoMode;
    sf::Uint32 style;

    loadVideoMode(videoMode, style);

    static Window win(videoMode, style);

    win.initSetScale(videoMode);

    return win;
}

float Window::getRescale()
{
    return rescale;
}

float Window::getRescaleT()
{
    return rescale_t;
}

void Window::setRescale(sf::VideoMode &  video, sf::Uint32 & style)
{
    rescale = (float(video.height)/1080.f)/(sf::VideoMode::getDesktopMode().height/1080.f);
    rescale_t = video.height/1080.f;

    window.create(video, "Shooter", style);

    window.setMouseCursorVisible(false);
}

void Window::initSetScale(sf::VideoMode &  video)
{
    rescale = (float(video.height)/1080.f);
    rescale_t = video.height/1080.f;
}

sf::RenderTexture & Window::getBoxRT()
{
    return boxRT;
}

sf::RenderTexture & Window::getBackground()
{
    return background;
}

float rad2deg(float rad)
{
    return (360 / (2 * 3.14)) * rad;
}

float deg2rad(float deg)
{
    return ((2 * 3.14) / 360) * deg;
} 

float calculateDistance(sf::Vector2f v1, sf::Vector2f v2)
{
    return sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y));
}