#include <SDL2/SDL.h>
#include "cstdlib"
#include "constants.h"
#include "MyGame.h"
#include "ScreenWriter.h"
#include "Entity.h"
#include "GameEntity.h"
#include "Atom.h"
#include "Bullet.h"
#include "Player.h"
#include "ScoreBoard.h"
#include "EntityRepository.h"

using namespace Support;
using namespace Engine;
using namespace GameEntities;
using namespace UIEntities;

bool MyGame::load(SDL_Renderer* renderer, SDL_Texture* textures[], ScreenWriter* screenWriter)
{
	Player* player = new Player(0, 0);
	bool resultPlayer = player->load(renderer, textures, screenWriter);
	delete player;

	Bullet* bullet = new Bullet(0, 0);
	bool resultBullet = bullet->load(renderer, textures, screenWriter);
	delete bullet;
	
	Atom* atom = new Atom(0, 0, 1, 1);
	bool resultAtom = atom->load(renderer, textures, screenWriter);
	delete atom;
	
	ScoreBoard* hidrogenScoreBoard = new ScoreBoard("Hidrogenio");
	bool resultHidrogenScoreBoard = hidrogenScoreBoard->load(renderer, textures, screenWriter);
	delete hidrogenScoreBoard;

	ScoreBoard* oxigenScoreBoard = new ScoreBoard("Oxigenio");
	bool resultOxigenScoreBoard = oxigenScoreBoard->load(renderer, textures, screenWriter);
	delete oxigenScoreBoard;
	
	return resultPlayer && resultBullet && resultAtom && resultHidrogenScoreBoard && resultOxigenScoreBoard;
}

void MyGame::setGameScene(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)
{
	Player* player = new Player(0, 0);
	player->setLife(2);
	entityRepository->addEntity(player);

	fillAtoms(entityRepository);

	addUIElements(UIEntityRepository);
}

void MyGame::onGameLoopStart(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)
{
	int atomsCount = 0;
	auto counter = [&](unsigned int id, GameEntity* gameEntity) -> bool 
	{
		if (gameEntity->type == "Atom")
		{
			atomsCount++;
		}
		return true;
	};
	entityRepository->iterate(counter);

	if (atomsCount < 3)
	{
		int x = 1 + (rand() % SCREEN_WIDTH);
		int y = 1 + (rand() % SCREEN_HEIGHT);
		int atomicNumber = 1;
		int atomicMass = 1;
		int zAngle = 1 + (rand() % 360); 
		if (x % 2 == 0)
		{
			atomicNumber = 8;
			atomicMass = 16;
			x = 0;
			zAngle = zAngle * -1;
		}
		else
		{
			y = 0;
		}

		Atom* atom = new Atom(x, y, atomicNumber, atomicMass);
		atom->setZAngle(zAngle);
		entityRepository->addEntity(atom);
	}
}

void MyGame::fillAtoms(EntityRepository<GameEntity>* entityRepository)
{
	struct AtomInfo {
		int x;
		int y;
		int atomicNumber;
		int atomicMass;
		double zAngle;
	};

	AtomInfo atomsInfo[4];
	atomsInfo[0].x = 50;
	atomsInfo[0].y = 25;
	atomsInfo[0].atomicNumber = 1;
	atomsInfo[0].atomicMass = 1;
	atomsInfo[0].zAngle = 180;

	atomsInfo[1].x = 500;
	atomsInfo[1].y = 400;
	atomsInfo[1].atomicNumber = 1;
	atomsInfo[1].atomicMass = 1;
	atomsInfo[1].zAngle = 70;

	atomsInfo[2].x = 25;
	atomsInfo[2].y = 450;
	atomsInfo[2].atomicNumber = 8;
	atomsInfo[2].atomicMass = 16;
	atomsInfo[2].zAngle = 140;

	atomsInfo[3].x = 300;
	atomsInfo[3].y = 50;
	atomsInfo[3].atomicNumber = 1;
	atomsInfo[3].atomicMass = 1;

	atomsInfo[3].zAngle = -110;

	for (int i = 0; i < 4; i++)
	{
		Atom* atom = new Atom(atomsInfo[i].x, atomsInfo[i].y, atomsInfo[i].atomicNumber, atomsInfo[i].atomicMass);
		atom->setZAngle(atomsInfo[i].zAngle);

		entityRepository->addEntity(atom);
	}
}

void MyGame::addUIElements(EntityRepository<Entity>* entityRepository)
{

	SDL_Color hidrogenColor;
	hidrogenColor.r = 210;
	hidrogenColor.g = 212;
	hidrogenColor.b = 225;
	hidrogenColor.a = 1;	
	ScoreBoard* scoreBoard = new ScoreBoard("Hidrogenio", 10, 1, hidrogenColor, 5, 5);
	scoreBoard->registerPlayerAtomCollisionListener();
	entityRepository->addEntity(scoreBoard);

	SDL_Color oxigenColor;
	oxigenColor.r = 30;
	oxigenColor.g = 144;
	oxigenColor.b = 255;
	oxigenColor.a = 1;	
	ScoreBoard* oxigenScoreBoard = new ScoreBoard("Oxigenio", 80, 8, oxigenColor, 270, 5);
	oxigenScoreBoard->registerPlayerAtomCollisionListener();
	entityRepository->addEntity(oxigenScoreBoard);

}
