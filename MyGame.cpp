#include <SDL2/SDL.h>
#include "MyGame.h"
#include "Atom.h"
#include "Bullet.h"
#include "Player.h"
#include "EntityRepository.h"

using namespace GameEntities;
using namespace Support;

bool MyGame::load(SDL_Renderer* renderer, SDL_Texture* textures[])
{
	Player* player = new Player(0, 0);
	bool resultPlayer = player->load(renderer, textures);
	delete player;

	Bullet* bullet = new Bullet(0, 0);
	bool resultBullet = bullet->load(renderer, textures);
	delete bullet;
	
	Atom* atom = new Atom(0, 0);
	bool resultAtom = atom->load(renderer, textures);
	delete atom;

	return resultPlayer && resultBullet && resultAtom;
}

void MyGame::setGameScene(EntityRepository* entityRepository)
{
	Player* player = new Player(0, 0);
	player->setLife(2);
	entityRepository->addEntity(player);

	fillAtoms(entityRepository);
}

void MyGame::fillAtoms(EntityRepository* entityRepository)
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
