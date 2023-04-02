#include <iostream>
#include "HuntAtoms.h"
#include "Player.h"
#include "Atom.h"
#include "Game.h"
#include "constants.h"
#include "ScoreBoard.h"
#include "AtomDAO.h"
#include "MoleculeDAO.h"
#include "LevelDAO.h"

using namespace Engine;
using namespace Engine::Support;
using namespace GameEntities;
using namespace UIEntities;
using namespace Data;
using namespace Scenes::Support;

Scenes::HuntAtoms::HuntAtoms(LevelData levelData)
{
	this->levelData = levelData;
}

int Scenes::HuntAtoms::load(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)
{
	Player* player = new Player(0, 0);
	player->setLife(2);
	entityRepository->addEntity(player);

	addUIElements(UIEntityRepository);

	MoleculeDAO moleculeDAO;
	moleculeDAO.loadData();

	atomGenerator = new AtomGenerator(levelData);

	SDL_Delay(1000);

	return Game::STATUS_IN_GAME;
}

void Scenes::HuntAtoms::onGameLoopStart(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository, ScreenWriter* screenWriter, const unsigned char* keys, bool isMouseDown)
{
	atomGenerator->setAtoms(entityRepository, UIEntityRepository);
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
