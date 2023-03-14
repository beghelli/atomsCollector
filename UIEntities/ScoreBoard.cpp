#include <SDL2/SDL.h>
#include <string>
#include "ScoreBoard.h"
#include "ScreenWriter.h"
#include "Message.h"
#include "Entity.h"
#include "EventsManager.h"
#include "PlayerAndAtomCollided.h"

using namespace Engine;
using namespace Support;
using namespace Events;

UIEntities::ScoreBoard::ScoreBoard(string label, int maxCapacity, int atomicNumber)
{
	this->label = label;
	this->maxCapacity = maxCapacity;
	this->atomicNumber = atomicNumber;
}

bool UIEntities::ScoreBoard::load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)
{
	Message otherElementsMessage(label, 25, 1, 0, 0, 80, 20);
	screenWriter->loadTextTexture(otherElementsMessage);

	return Entity::load(renderer, textures, screenWriter);	
}

void UIEntities::ScoreBoard::update(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown)
{
	
}

void UIEntities::ScoreBoard::render(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)
{
	int leftLimit = 5;
	int topLimit = 5;

	int otherMessageWidth = 80;
	int otherMessageHeight = 20;

	Message otherElementsMessage(label, 25, 1, leftLimit, topLimit, otherMessageWidth, otherMessageHeight);
	
	int space = 10;
	SDL_Rect* capacityBar = new SDL_Rect();
	capacityBar->x = leftLimit + otherMessageWidth + space;
	capacityBar->y = topLimit;
	capacityBar->w = otherMessageWidth * 2;
	capacityBar->h = otherMessageHeight;

	SDL_Rect* capacityBarContent = new SDL_Rect();
	capacityBarContent->x = capacityBar->x + 1;
	capacityBarContent->y = capacityBar->y + 1;
	int filledPercentage = (otherAtomsQuantity * 100) / maxCapacity;
	capacityBarContent->w = ((capacityBar->w - 2) / 100) * filledPercentage; 
	capacityBarContent->h = capacityBar->h - 2;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderDrawRect(renderer, capacityBar);

	SDL_SetRenderDrawColor(renderer, 255, 165, 0, 1);
	SDL_RenderFillRect(renderer, capacityBarContent);
	screenWriter->write(otherElementsMessage);
}

void UIEntities::ScoreBoard::registerPlayerAtomCollisionListener()
{
	auto listener = [&](Event* event) -> void
	{
		PlayerAndAtomCollided* castedEvent = dynamic_cast<PlayerAndAtomCollided*>(event);
		if (castedEvent->atomicNumber == atomicNumber)
		{
			otherAtomsQuantity += castedEvent->atomicMass;
		}
	};

	EventsManager* eventsMgr = EventsManager::Get();
	eventsMgr->listenFor("PlayerAndAtomCollided", listener);
}
