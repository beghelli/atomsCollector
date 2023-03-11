#include <string>
#include "Message.h"

using namespace std;

Support::Message::Message(string text, int fontSize, int fontId, int positionX, int positionY, int width, int height)
{
	this->text = text;
	this->fontSize = fontSize;
	this->fontId = fontId;
	this->positionX = positionX;
	this->positionY = positionY;
	this->width = width;
	this->height = height;	
}

string Support::Message::getText()
{
	return text;
}

const char* Support::Message::getTextChar()
{
	return getText().c_str();
}

int Support::Message::getFontSize()
{
	return fontSize;
}

int Support::Message::getFontId()
{
	return fontId;
}

int Support::Message::getPositionX()
{
	return positionX;
}

int Support::Message::getPositionY()
{
	return positionY;	
}

int Support::Message::getWidth()
{
	return width;
}
		
int Support::Message::getHeight()
{
	return height;
}
