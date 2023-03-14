#include <string>
#include "PlayerAndAtomCollided.h"

Events::PlayerAndAtomCollided::PlayerAndAtomCollided(int atomicNumber, int atomicMass)
{
	this->id = this->getId();
	this->atomicNumber = atomicNumber;
	this->atomicMass = atomicMass;
}

string Events::PlayerAndAtomCollided::getId()
{
	return "PlayerAndAtomCollided";
}
