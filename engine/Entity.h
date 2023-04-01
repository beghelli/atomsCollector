#pragma once
#include "string"
#include <SDL2/SDL.h>
#include "ScreenWriter.h"

using namespace std;
using namespace Engine::Support;

namespace Engine
{
	class Entity
	{
		protected:
			unsigned int id;
			int x;
			int y;
			int entityHeight;
			int entityWidth;
			string entityTextureFile;
			int entityTextureIndex;
			string classType;
			string instanceType;
			
		public:
			void setId(unsigned int id);
			unsigned int getId();
			int getX();
			int getY();
			int getHeight();
			int getWidth();
			string getClassType();
			string getInstanceType();
			bool load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter);
			void destroy(SDL_Texture* textures[]);	

			static const string DEFAULT_INSTANCE_TYPE;

			virtual void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)=0;
			virtual void render(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)=0;
	};

}
