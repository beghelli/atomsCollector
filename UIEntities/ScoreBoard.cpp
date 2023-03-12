#include <SDL2/SDL.h>
#include "ScoreBoard.h"
#include "ScreenWriter.h"
#include "Message.h"
#include "Entity.h"

using namespace Support;
using namespace Engine;

bool UIEntities::ScoreBoard::load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)
{
	return Entity::load(renderer, textures, screenWriter);	
}

void UIEntities::ScoreBoard::update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)
{
	
}

void UIEntities::ScoreBoard::render(SDL_Renderer* renderer, SDL_Texture* textures[])
{

}

