#pragma once
#include <string>

using namespace std;

namespace Engine
{
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
}
