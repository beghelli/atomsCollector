#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "ScreenWriter.h"
#include "Message.h"

using namespace std;
using namespace Engine::Support;

Engine::Support::ScreenWriter::ScreenWriter(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

Engine::Support::ScreenWriter::~ScreenWriter()
{
	TTF_CloseFont(font);
	for (TextTextureRecord textureRecord : textures)
	{
		SDL_DestroyTexture(textureRecord.texture);
	}
	textures.clear();
}

bool Engine::Support::ScreenWriter::initialize()
{
	bool success = true;
	if (TTF_Init() == -1)
	{
		cout << "SDL_TTF could not be initialized. Error: " << TTF_GetError() << endl;
		success = false;
	}

	return success;
}

bool Engine::Support::ScreenWriter::load()
{
	int fontSize = 100;
	string fontPath = "." + PATH_SEPARATOR + ASSETS_FOLDER + PATH_SEPARATOR + "freeSans.ttf";
	font = TTF_OpenFont(fontPath.c_str(), fontSize);

	if (font == NULL)
	{
		cout << "Failed loading font. Error: " << TTF_GetError() << endl;
		return false;
	}

	return true;
}

void Engine::Support::ScreenWriter::write(Message message)
{
	TextTextureRecord workingTextureRecord = loadTextTexture(message);

	if (workingTextureRecord.texture)
	{
		SDL_Rect body;
		body.x = message.getPositionX();
		body.y = message.getPositionY();
		body.h = message.getHeight();
		body.w = message.getWidth();

		SDL_RenderCopyEx(renderer, workingTextureRecord.texture, NULL, &body, 0, NULL, SDL_FLIP_NONE);
	}
}

TextTextureRecord Engine::Support::ScreenWriter::loadTextTexture(Message message)
{
	TextTextureRecord workingTextureRecord;
	bool textureLoaded = false;
	for (TextTextureRecord textureRecord : textures)
	{
		if (textureRecord.text == message.getText())
		{
			workingTextureRecord = textureRecord;
			textureLoaded = true;
			break;
		}
	}

	if (! textureLoaded)
	{
		cout << "Loading Text Texture" << endl;
		SDL_Color textColor = { 0, 0, 0 };
		SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, message.getText().c_str(), textColor);
		if (textSurface == NULL)
		{
			cout << "Text surface could not be loaded. Error " << TTF_GetError() << endl;
		}
		else
		{
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (texture == NULL)
			{
				cout << "Text texture could not be created from surface. Error " << SDL_GetError();
			}
			else
			{
				workingTextureRecord.text = message.getText();
				workingTextureRecord.texture = texture;
				textures.push_back(workingTextureRecord);
				textureLoaded = true;
			}
			SDL_FreeSurface(textSurface);
		}
	}

	return workingTextureRecord;
}
