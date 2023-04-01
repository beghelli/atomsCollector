#include <string>
#include "Message.h"

using namespace std;

Engine::Support::Message::Message(string text, int fontSize, int fontId, int positionX, int positionY, int width, int height)
{
	this->text = text;
	this->fontSize = fontSize;
	this->fontId = fontId;
	this->positionX = positionX;
	this->positionY = positionY;
	this->width = width;
	this->height = height;
}

string Engine::Support::Message::getText()
{
	return text;
}

int Engine::Support::Message::getFontSize()
{
	return fontSize;
}

int Engine::Support::Message::getFontId()
{
	return fontId;
}

int Engine::Support::Message::getPositionX()
{
	return positionX;
}

int Engine::Support::Message::getPositionY()
{
	return positionY;
}

int Engine::Support::Message::getWidth()
{
	return width;
}

int Engine::Support::Message::getHeight()
{
	return height;
}
