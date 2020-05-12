#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

constexpr int alpha = 150;

class Window
{
private:
    static bool instance;
    sf::RenderWindow window;
    sf::Font font0;
    sf::Font font1;
    sf::Font font2;
    sf::Font font3;

    float rescale;
	float rescale_t;

    sf::RenderTexture background;
	sf::RenderTexture boxRT;

    static void loadVideoMode(sf::VideoMode & video, sf::Uint32 & style);
    static Window & initialize();

    Window(sf::VideoMode & video, sf::Uint32 & style);
    ~Window();

public:
    static Window & get();
    static sf::Font & getFont(int x);

    void draw(sf::Drawable * object);
    bool isOpen();
    void clear(sf::Color color);
    void display();
    void close();
    void setView(sf::View & view);
    void setDefaultView();
    void setMouseCursorVisible(bool value);
    bool pollEvent(sf::Event & event);
    sf::Vector2i getMousePosition();
    sf::Vector2f getViewCenter();
    sf::Vector2u getSize();
    sf::View getView();

    float getRescale();
    float getRescaleT();
    void setRescale(sf::VideoMode &  video, sf::Uint32 & style);
	void initSetScale(sf::VideoMode &  video);

    sf::RenderTexture & getBoxRT();
    sf::RenderTexture & getBackground();
};

constexpr auto GetWindow = &Window::get;
constexpr auto GetFont = &Window::getFont;

float rad2deg(float rad);
float deg2rad(float deg);
float calculateDistance(sf::Vector2f v1, sf::Vector2f v2);