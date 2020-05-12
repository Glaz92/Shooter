#include "TxtBox.h"
#include "Window.h"

TxtBox::TxtBox(sf::Vector2f s, sf::Vector2f pos, bool in, bool onlyNumbers)
	: input(in), box(s), position(pos), size(s), active(false), onlyNum(onlyNumbers)
{
	font.loadFromFile("data/font/calibri.ttf");
	txt.setFont(font);
	txt.setString("");
	txt.setFillColor(sf::Color::Black);
	txt.setCharacterSize(15);

	box.setOutlineThickness(2);
	box.setOutlineColor(sf::Color::Black);
	box.setFillColor(sf::Color(230, 230, 230));

	box.setPosition(position.x, position.y);
	txt.setPosition(position.x + 5, position.y + 3);
}


TxtBox::~TxtBox(void)
{
}

void TxtBox::draw()
{
	if(input)
	{
		if(active)
		{
			inputTxt();
			box.setOutlineColor(sf::Color::Red);
		}
		else
		{
			box.setOutlineColor(sf::Color::Black);
		}

		if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
		{
			if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
			{
				box.setOutlineColor(sf::Color(60,120,180));
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
					active=true;
			}
			else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				active=false;
		}
		else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			active=false;
	}
	else
		box.setOutlineColor(sf::Color::Black);

	txt.setString(ss.str());

	GetWindow().draw(&box);
	GetWindow().draw(&txt);
}

void TxtBox::inputTxt()
{
	sf::Event ev;
	
	while(GetWindow().pollEvent(ev))
	{
		if(ev.type == sf::Event::Closed)
			GetWindow().close();
		if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::BackSpace)
		{
			std::string tmpS=ss.str();
			ss.str("");
			ss << tmpS.substr(0,tmpS.length()-1);
		//	sf::sleep(sf::milliseconds(100));
		}
		if(ev.type == sf::Event::TextEntered)
		{
			if(!onlyNum)
			{
				if(((ev.text.unicode>47 && ev.text.unicode<58) || (ev.text.unicode>64 && ev.text.unicode<91) || (ev.text.unicode>96 && ev.text.unicode<123) || ev.text.unicode==46) && ss.str().length()<25)
				{
					char tmp=ev.text.unicode;
					ss << tmp;
				}
			}
			else
			{
				if(((ev.text.unicode>47 && ev.text.unicode<58) && ss.str().length()<6))
				{
					char tmp=ev.text.unicode;
					ss << tmp;
				}
			}
		}
	}
}

void TxtBox::rescale(float x)
{
	x = x > 2 ? 2 : 1;
}