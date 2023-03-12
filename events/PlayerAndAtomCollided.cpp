#include <string>
#include "PlayerAndAtomCollided.h"

Events::PlayerAndAtomCollided::PlayerAndAtomCollided(int atomicMass)
{
	this->id = this->getId();
	this->atomicMass = atomicMass;
}

string Events::PlayerAndAtomCollided::getId()
{
	return "PlayerAndAtomCollided";
}
