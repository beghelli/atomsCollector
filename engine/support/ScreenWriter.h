#pragma once
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Message.h"

using namespace std;
using namespace Engine::Support;

namespace Engine
{
	namespace Support
	{
		typedef struct TextTextureRecord {
			string text;
			SDL_Texture* texture;
		} TextTextureRecord;

		class ScreenWriter
		{	
			private:
				SDL_Renderer* renderer;
				TTF_Font* font;
				vector<TextTextureRecord> textures;

			public:
				ScreenWriter(SDL_Renderer* renderer);
				~ScreenWriter();
				bool initialize();
				bool load();
				TextTextureRecord loadTextTexture(Message message);
				void write(Message message);
		};
	}
}
