#include <vector>
#include "cstdlib"
#include "constants.h"
#include "AtomGenerator.h"
#include "HuntAtoms.h"
#include "Atom.h"
#include "EntityRepository.h"
#include "GameEntity.h"
#include "Entity.h"
#include "MoleculeDAO.h"

using namespace Scenes;
using namespace Scenes::Support;
using namespace GameEntities;
using namespace Engine::Support;
using namespace Engine;
using namespace Data;

Scenes::Support::AtomGenerator::AtomGenerator(MoleculeData sceneDesiredMolecule, int desiredAtomsAppearanceChance)
{
	this->sceneDesiredMolecule = sceneDesiredMolecule;
	this->desiredAtomsAppearanceChance = desiredAtomsAppearanceChance;
}

void Scenes::Support::AtomGenerator::setAtoms(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)
{
	int atomsCount = 0;
	vector<GameEntity *> atoms;
	
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
