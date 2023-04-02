#pragma once
#include <map>
#include "Atom.h"
#include "EntityRepository.h"
#include "GameEntity.h"
#include "Entity.h"
#include "MoleculeDAO.h"
#include "LevelDAO.h"
#include "AtomDAO.h"

using namespace Engine::Support;
using namespace Engine;
using namespace Data;

namespace Scenes
{
	namespace Support
	{
		// Decides which atom entities should be added into the passed scene, based on the
		// scene desired molecule, the current available scene atoms and the atom recipients
		// storage values.
		class AtomGenerator
		{
			private:
				LevelData levelData;
				map<int, AtomData> appearenceChanceMap;
				MoleculeData desiredMoleculeData;

				void calculateAtomsAppearanceMap();

			public:
				AtomGenerator(LevelData levelData);
				void setAtoms(EntityRepository<GameEntity>* entityRepository, EntityRepository<Entity>* UIEntityRepository);
		};
	}
}
