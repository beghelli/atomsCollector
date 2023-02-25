#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "ScreenWriter.h"

using namespace std;

Support::ScreenWriter::ScreenWriter(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

Support::ScreenWriter::~ScreenWriter()
{
	TTF_CloseFont(font);
	for (TextTextureRecord textureRecord : textures)
	{
		SDL_DestroyTexture(textureRecord.texture);
	}
	textures.clear();
}

bool Support::ScreenWriter::initialize()
{
	bool success = true;
	if (TTF_Init() == -1)
	{
		cout << "SDL_TTF could not be initialized. Error: " << TTF_GetError() << endl;
		success = false;
	}

	return success;
}

bool Support::ScreenWriter::load()
{
	int fontSize = 50;
	string fontPath = ".\\" + ASSETS_FOLDER + "\\" + "akira.otf";
	font = TTF_OpenFont(fontPath.c_str(), fontSize); 

	if (font == NULL)
	{
		cout << "Failed loading font. Error: " << TTF_GetError() << endl;
		return false;
	}

	return true;
}

void Support::ScreenWriter::write(string message)
{
	TextTextureRecord workingTextureRecord;
	bool textureLoaded = false;
	for (TextTextureRecord textureRecord : textures)
	{
		if (textureRecord.text == message)
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
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), textColor);
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
				workingTextureRecord.text = message;
				workingTextureRecord.texture = texture;
				textures.push_back(workingTextureRecord);
				textureLoaded = true;
			}
			SDL_FreeSurface(textSurface);
		}
	}

	if (textureLoaded)
	{
		SDL_Rect body;
		body.x = 50;
		body.y = 50;
		body.h = 100;
		body.w = 650;

		SDL_RenderCopyEx(renderer, workingTextureRecord.texture, NULL, &body, 0, NULL, SDL_FLIP_NONE);
	}

	return;
}
