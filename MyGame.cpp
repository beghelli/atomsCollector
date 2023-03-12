#include <SDL2/SDL.h>
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
	
	Atom* atom = new Atom(0, 0);
	bool resultAtom = atom->load(renderer, textures, screenWriter);
	delete atom;
	
	ScoreBoard* scoreBoard = new ScoreBoard();
	bool resultScoreBoard = scoreBoard->load(renderer, textures, screenWriter);
	delete scoreBoard;
	
	return resultPlayer && resultBullet && resultAtom;
}

void MyGame::setGameScene(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)
{
	Player* player = new Player(0, 0);
	player->setLife(2);
	entityRepository->addEntity(player);

	fillAtoms(entityRepository);

	addUIElements(UIEntityRepository);
}

void MyGame::fillAtoms(EntityRepository<GameEntity>* entityRepository)
{
	struct AtomInfo {
		int x;
		int y;
		double zAngle;
	};

	AtomInfo atomsInfo[4];
	atomsInfo[0].x = 50;
	atomsInfo[0].y = 25;
	atomsInfo[0].zAngle = 180;

	atomsInfo[1].x = 500;
	atomsInfo[1].y = 400;
	atomsInfo[1].zAngle = 70;

	atomsInfo[2].x = 25;
	atomsInfo[2].y = 450;
	atomsInfo[2].zAngle = 140;

	atomsInfo[3].x = 300;
	atomsInfo[3].y = 50;
	atomsInfo[3].zAngle = -110;

	for (int i = 0; i < 4; i++)
	{
		Atom* atom = new Atom(atomsInfo[i].x, atomsInfo[i].y);
		atom->setZAngle(atomsInfo[i].zAngle);

		entityRepository->addEntity(atom);
	}
}

void MyGame::addUIElements(EntityRepository<Entity>* entityRepository)
{
	ScoreBoard* scoreBoard = new ScoreBoard();
	entityRepository->addEntity(scoreBoard);
}
