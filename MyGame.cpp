#include <iostream>
#include <SDL2/SDL.h>
#include "constants.h"
#include "MyGame.h"
#include "ScreenWriter.h"
#include "Atom.h"
#include "Bullet.h"
#include "Player.h"
#include "ScoreBoard.h"
#include "HuntAtoms.h"
#include "AtomDAO.h"
#include "LevelDAO.h"

using namespace Data;
using namespace Engine::Support;
using namespace GameEntities;
using namespace UIEntities;
using namespace Scenes;

bool MyGame::load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)
{
	Player* player = new Player(0, 0);
	bool resultPlayer = player->load(renderer, textures, screenWriter);
	delete player;

	Bullet* bullet = new Bullet(0, 0);
	bool resultBullet = bullet->load(renderer, textures, screenWriter);
	delete bullet;

	AtomData atomData;
	Atom* atom = new Atom(0, 0, atomData);
	bool resultAtom = atom->load(renderer, textures, screenWriter);
	delete atom;

	ScoreBoard* hidrogenScoreBoard = new ScoreBoard("Hidrogenio");
	bool resultHidrogenScoreBoard = hidrogenScoreBoard->load(renderer, textures, screenWriter);
	delete hidrogenScoreBoard;

	ScoreBoard* oxigenScoreBoard = new ScoreBoard("Oxigenio");
	bool resultOxigenScoreBoard = oxigenScoreBoard->load(renderer, textures, screenWriter);
	delete oxigenScoreBoard;

	bool resultLoadLevelsData = LevelDAO::loadData();

	return resultPlayer && resultBullet && resultAtom && resultHidrogenScoreBoard && resultOxigenScoreBoard && resultLoadLevelsData;
}

bool MyGame::renderMenus(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown)
{
	SDL_SetRenderDrawColor(renderer, 50, 50, 255, 1);
	SDL_RenderClear(renderer);

	Message message("Pressione ENTER para começar!", 25, 1, 150, 150, 550, 100);
	screenWriter->write(message);

	SDL_RenderPresent(renderer);

	if (keys[SDL_SCANCODE_RETURN])
	{
		LevelDAO levelDAO;
		HuntAtoms* huntAtoms = new HuntAtoms(levelDAO.getById("first"));
		loadScene(huntAtoms);
	}

	return true;
}

void MyGame::renderLoadingScreen(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
	SDL_RenderClear(renderer);

	int messageWidth = 500;
	int messageHeight = 100;
	Message message("Carregando", 25, 1, (SCREEN_WIDTH / 2) - (messageWidth / 2), (SCREEN_HEIGHT / 2) - (messageHeight / 2), messageWidth, messageHeight);
	screenWriter->write(message);

	SDL_RenderPresent(renderer);
}
