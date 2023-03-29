#include <iostream>
#include "cstdlib"
#include "HuntAtoms.h"
#include "Player.h"
#include "Atom.h"
#include "Game.h"
#include "constants.h"
#include "ScoreBoard.h"
#include "AtomDAO.h"
#include "MoleculeDAO.h"

using namespace Engine;
using namespace GameEntities;
using namespace UIEntities;
using namespace Data;

int Scenes::HuntAtoms::load(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)
{
	Player* player = new Player(0, 0);
	player->setLife(2);
	entityRepository->addEntity(player);

	fillAtoms(entityRepository);

	addUIElements(UIEntityRepository);

	MoleculeDAO moleculeDAO;
	moleculeDAO.loadData();

	SDL_Delay(1000);

	return Game::STATUS_IN_GAME;
}

void Scenes::HuntAtoms::onGameLoopStart(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository, ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown)
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
		int atomicMass = 1;
		int zAngle = 1 + (rand() % 360);
		int atomicNumber = 1 + (rand() % 7);
		if (x % 2 == 0)
		{
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

void Scenes::HuntAtoms::fillAtoms(EntityRepository<GameEntity>* entityRepository)
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

void Scenes::HuntAtoms::addUIElements(EntityRepository<Entity>* entityRepository)
{
	SDL_Color hidrogenColor;

	AtomDAO atomDAO;
	auto atomsData = atomDAO.getById("1H1");
	vector<int> trackedHydrogenAtomicNumber{atomsData.atomicNumber};
	ScoreBoard* hidrogenScoreBoard = new ScoreBoard(atomsData.name, 10, trackedHydrogenAtomicNumber, atomsData.color, 5, 5);
	hidrogenScoreBoard->registerPlayerAtomCollisionListener();
	entityRepository->addEntity(hidrogenScoreBoard);

	atomsData = atomDAO.getById("8O16");
	vector<int> trackedOxigenAtomicNumber{atomsData.atomicNumber};
	ScoreBoard* oxigenScoreBoard = new ScoreBoard(atomsData.name, 80, trackedOxigenAtomicNumber, atomsData.color, 270, 5);
	oxigenScoreBoard->registerPlayerAtomCollisionListener();
	entityRepository->addEntity(oxigenScoreBoard);

	SDL_Color otherColor;
	otherColor.r = 245;
	otherColor.g = 40;
	otherColor.b = 145;
	otherColor.a = 1;
	vector<int> trackedAtomicNumbers{2,3,4,5,6,7};
	ScoreBoard* otherScoreBoard = new ScoreBoard("Outros", 150, trackedAtomicNumbers, otherColor, 535, 5);
	otherScoreBoard->registerPlayerAtomCollisionListener();
	entityRepository->addEntity(otherScoreBoard);
}
