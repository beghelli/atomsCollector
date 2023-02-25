#pragma once
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

namespace Support
{
	class ScreenWriter
	{
		typedef struct TextTextureRecord {
			string text;
			SDL_Texture* texture;
		} TextTextureRecord;

		private:
			SDL_Renderer* renderer;
			TTF_Font* font;
			vector<TextTextureRecord> textures;

		public:
			ScreenWriter(SDL_Renderer* renderer);
			~ScreenWriter();
			bool initialize();
			bool load();
			void write(string message);
	};
}
