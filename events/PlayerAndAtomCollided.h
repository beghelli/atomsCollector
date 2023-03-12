#pragma once
#include "Event.h"

using namespace Support;

namespace Events
{
	class PlayerAndAtomCollided : public Event
	{
		public:
			int atomicMass;
			PlayerAndAtomCollided(int atomicMass);
			~PlayerAndAtomCollided();
		protected:
			string getId();
	};
}
