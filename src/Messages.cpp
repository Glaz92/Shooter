#include "Messages.h"
#include "Window.h"

Cmessages::Cmessages(float xx, float yy)
    : time(450), txt("...",font,21), MAX(5), rozX(xx), rozY(yy), shape(sf::Vector2f(360,27))
{
    font.loadFromFile("data\\font\\CodenameCoderFree4F-Bold.TTF");
    shape.setFillColor(sf::Color(5,5,5,75));
}
Cmessages::~Cmessages()
{}

void Cmessages::draw()
{
    pos=0;

    float xx = GetWindow().getViewCenter().x;
    float yy = GetWindow().getViewCenter().y-sf::VideoMode::getDesktopMode().height/2+14;

    while(message.size()>MAX)
    {
        erase(); 
    }  

    for(int i=message.size()-1;i>-1;i--)
    {
        if(!isEmpty[i])
        {
            shape.setPosition(xx+rozX/2-380,yy+pos);
            GetWindow().draw(&shape);
        }

        txt.setString(message[i]);
        txt.setFillColor(colorM[i]);

        txt.setPosition(xx+rozX/2-370,yy+pos);
        GetWindow().draw(&txt);
        pos+=32;
    }

    time--;
    if(time==0)
    {
        time=200;
        addEmptyMessage();
    }
}

void Cmessages::addMessage(std::string text, sf::Color ccc)
{
    message.push_back(text);
    colorM.push_back(ccc);
    isEmpty.push_back(false);
} 

void Cmessages::addEmptyMessage()
{
    message.push_back("  ");
    colorM.push_back(sf::Color::White);
    isEmpty.push_back(true);
}

void Cmessages::erase() 
{
    message.erase(message.begin());
    colorM.erase(colorM.begin());
    isEmpty.erase(isEmpty.begin());
}