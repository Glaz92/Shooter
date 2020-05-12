#include "Button.h"
#include "Window.h"

Button::Button(sf::Vector2f pos, std::string text)
	: backColor(sf::Color(130,130,130,alpha))
{
	position=pos;

	button.setFillColor(sf::Color(130,130,130));
	button.setOutlineThickness(3);
	button.setOutlineColor(sf::Color(100,100,100));

	txt.setFont(GetFont(0));
	txt.setString(text);
	txt.setFillColor(sf::Color::Black);
	txt.setCharacterSize(15);

	size.x=txt.getGlobalBounds().width+20;
	size.y=txt.getGlobalBounds().height+10;

	button.setSize(size);
	button.setPosition(pos.x,pos.y);
	txt.setPosition(pos.x+10,pos.y+1);
}

Button::Button(sf::Vector2f pos, std::string text, sf::Vector2f s)
	: backColor(sf::Color(130,130,130,alpha))
{
	position=pos;

	button.setFillColor(sf::Color(130,130,130));

	txt.setFont(GetFont(0));
	txt.setString(text);
	txt.setFillColor(sf::Color::Black);
	txt.setCharacterSize(15);

	if(txt.getGlobalBounds().width<s.x && txt.getGlobalBounds().height<s.y)
	{
		size=s;
	}
	else
	{
		size.x=txt.getGlobalBounds().width+20;
		size.y=txt.getGlobalBounds().height+10;
	}

	button.setSize(size);
	button.setPosition(pos.x,pos.y);

	txt.setPosition(pos.x+5,float(int(pos.y+(size.y-txt.getGlobalBounds().height)/2-4)));
}

Button::Button(sf::Vector2f pos, std::string text, sf::Vector2f s, int font, int fontSize)
	: backColor(sf::Color(130,130,130,alpha))
{
	position=pos;

	button.setFillColor(sf::Color(130,130,130));

	txt.setFont(GetFont(font));
	txt.setString(text);
	txt.setFillColor(sf::Color::Black);
	txt.setCharacterSize(fontSize);

	if(txt.getGlobalBounds().width<s.x && txt.getGlobalBounds().height<s.y)
	{
		size=s;
	}
	else
	{
		size.x=txt.getGlobalBounds().width+20;
		size.y=txt.getGlobalBounds().height+10;
	}

	button.setSize(size);
	button.setPosition(pos.x,pos.y);

	txt.setPosition(pos.x+5,float(int(pos.y+(size.y-txt.getGlobalBounds().height)/2-4)));
}

Button::Button(sf::Vector2f pos, std::string text, sf::Vector2f s, int font, int fontSize, sf::Color fontColor, sf::Color _backColor)
	: backColor(_backColor)
{
	position=pos;

	button.setFillColor(backColor);

	txt.setFont(GetFont(font));
	txt.setString(text);
	txt.setFillColor(fontColor);
	txt.setCharacterSize(fontSize);

	if(txt.getGlobalBounds().width<s.x && txt.getGlobalBounds().height<s.y)
	{
		size=s;
	}
	else
	{
		size.x=txt.getGlobalBounds().width+20;
		size.y=txt.getGlobalBounds().height+10;
	}

	button.setSize(size);
	button.setPosition(pos.x,pos.y);

	txt.setPosition(pos.x+5,float(int(pos.y+(size.y-txt.getGlobalBounds().height)/2-4)));
}

Button::~Button()
{
}


void Button::draw()
{
	button.setPosition(GetWindow().getViewCenter().x - GetWindow().getSize().x / 2 + position.x,
					   GetWindow().getViewCenter().y - GetWindow().getSize().y / 2 + position.y);
	txt.setPosition(10 + GetWindow().getViewCenter().x - GetWindow().getSize().x/2 + position.x,
					1 + GetWindow().getViewCenter().y - GetWindow().getSize().y/2 + position.y);

	GetWindow().draw(&button);
	GetWindow().draw(&txt);
}

void Button::drawInPlace(sf::Vector2f pos)
{
	position=pos;
	button.setPosition(pos.x,pos.y);
	txt.setPosition(pos.x,pos.y);
	GetWindow().draw(&button);
	GetWindow().draw(&txt);
}

void Button::drawInPlace(sf::Vector2f pos, sf::Vector2f drawPos)
{
	position=pos;
	button.setPosition(drawPos.x,drawPos.y);
	txt.setPosition(drawPos.x,drawPos.y);
	GetWindow().draw(&button);
	GetWindow().draw(&txt);
}

bool Button::isClick()
{
	button.setFillColor(backColor);
	if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
		if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
		{
			button.setFillColor(sf::Color(60,120,180,alpha));
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
				if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
					if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
						return true;
			}
		}

	return false;
}

bool Button::isClickRight()
{
	button.setFillColor(backColor);
	if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
		if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
		{
			button.setFillColor(sf::Color(60,120,180,alpha));
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				while(sf::Mouse::isButtonPressed(sf::Mouse::Right));
				if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
					if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
						return true;
			}
		}
	


	return false;
}

bool Button::isPressed()
{

	button.setFillColor(backColor);
	if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
		if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
		{
			button.setFillColor(sf::Color(60,120,180));
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
			//	while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
				sf::sleep(sf::milliseconds(65));
				if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
					if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
						return true;
			}
		}

	return false;
}

bool Button::isPressedRight()
{

	button.setFillColor(backColor);
	if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
		if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
		{
			button.setFillColor(sf::Color(60,120,180));
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
			//	while(sf::Mouse::isButtonPressed(sf::Mouse::Right));
				sf::sleep(sf::milliseconds(65));
				if(GetWindow().getMousePosition().x>position.x && GetWindow().getMousePosition().x<position.x+size.x)
					if(GetWindow().getMousePosition().y>position.y && GetWindow().getMousePosition().y<position.y+size.y)
						return true;
			}
		}
	


	return false;
}

void Button::rescale(float x)
{
	position.x = position.x*x;
	position.y = position.y*x;

	size.x = size.x*x;
	size.y = size.y*x;

	button.setPosition(position);
	button.setSize(size);

	txt.setCharacterSize(txt.getCharacterSize() * x);
}
