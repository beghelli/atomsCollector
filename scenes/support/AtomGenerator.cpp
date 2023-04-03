#include <iostream>
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
#include "LevelDAO.h"
#include "AtomDAO.h"

using namespace Scenes;
using namespace Scenes::Support;
using namespace GameEntities;
using namespace Engine::Support;
using namespace Engine;
using namespace Data;

Scenes::Support::AtomGenerator::AtomGenerator(LevelData levelData)
{
	this->levelData = levelData;
	MoleculeDAO moleculeDAO;
	this->desiredMoleculeData = moleculeDAO.getById(levelData.desiredMoleculeId);
	calculateAtomsAppearanceMap();
}

void Scenes::Support::AtomGenerator::setAtoms(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository)
{
	int atomsCount = entityRepository->getEntityCount("Atom", Entity::DEFAULT_INSTANCE_TYPE);

	if (atomsCount < levelData.maximumAtomsCount)
	{
		AtomData atomData;
		int desiredAtomSeed = 1 + (rand() % 100);
		if (desiredAtomSeed <= levelData.desiredAtomsAppearanceChance)
		{
			int atomSeed = 1 + (rand() % 100);

			for (auto pair : appearenceChanceMap)
			{
				int chance = pair.first;
				if (DEBUG)
				{
					cout << "Atom seed value: " << atomSeed << endl;
				}
				if (atomSeed <= chance)
				{
					atomData = pair.second;
					break;
				}
			}
		}
		else
		{
			AtomDAO atomDAO;
			vector<string> excludeIds;
			for (auto item : desiredMoleculeData.formula)
			{
				excludeIds.push_back(item.atomId);
			}
			atomData = atomDAO.getRandomBut(excludeIds);
		}

		if (DEBUG)
		{
			cout << "Selected atom id: " << atomData.id << endl;
		}

		int x = 1 + (rand() % SCREEN_WIDTH);
		int y = 1 + (rand() % SCREEN_HEIGHT);
		int atomicMass = atomData.atomicMass;
		int zAngle = 1 + (rand() % 360);
		int atomicNumber = atomData.atomicNumber;
		if (x % 2 == 0)
		{
			x = 0;
			zAngle = zAngle * -1;
		}
		else
		{
			y = 0;
		}

		Atom* atom = new Atom(x, y, atomData);
		atom->setZAngle(zAngle);
		entityRepository->addEntity(atom);
	}
}

void Scenes::Support::AtomGenerator::calculateAtomsAppearanceMap()
{
	AtomDAO atomDAO;

	int lastChance = 0;
	for (auto item : desiredMoleculeData.formula)
	{
		int chance = (100 * item.quantity) / desiredMoleculeData.totalAtomsCount;
		appearenceChanceMap[chance + lastChance] = atomDAO.getById(item.atomId);
		lastChance = chance;
	}

	if (DEBUG)
	{
		for (auto item : appearenceChanceMap)
		{
			cout << "Chance for " << item.second.id << " to appear: " << item.first << endl;
		}
	}
}
