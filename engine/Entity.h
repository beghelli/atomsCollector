#pragma once
#include "string"
#include <SDL2/SDL.h>

using namespace std; 

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
			
		public:
			void setId(unsigned int id);
			unsigned int getId();
			int getX();
			int getY();
			int getHeight();
			int getWidth();
			bool load(SDL_Renderer* renderer, SDL_Texture* textures[]);
			void destroy(SDL_Texture* textures[]);
			
			string type;

			virtual void update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)=0;
			virtual void render(SDL_Renderer* renderer, SDL_Texture* textures[])=0;
			virtual bool shouldDestroy()=0;
	};

}
