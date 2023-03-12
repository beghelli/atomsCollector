#pragma once
#include <string>

using namespace std;

namespace Support
{
	class Event
	{
		public:
			string id;
			void trigger();

		protected:
			virtual string getId()=0;
	};
}
