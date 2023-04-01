#pragma once
#include "Event.h"

using namespace Engine::Support;

namespace Events
{
	class PlayerAndAtomCollided : public Event
	{
		public:
			int atomicMass;
			int atomicNumber;
			PlayerAndAtomCollided(int atomicNumber, int atomicMass);
			~PlayerAndAtomCollided();
		protected:
			string getId();
	};
}
