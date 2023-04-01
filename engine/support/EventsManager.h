#pragma once
#include <functional>
#include <vector>
#include <string>
#include "Event.h"

using namespace std;
using namespace Engine::Support;

namespace Engine
{
	namespace Support
	{
		typedef struct EventListener {
			string event;
			function<void(Event* event)> callback;
		} EventListener;

		class EventsManager
		{
			private:
				static EventsManager* eventsManager;
				vector<EventListener> listeners;

			public:
				static EventsManager* Get();
				void listenFor(string event, function<void(Event* event)> listenerFunction);
				void trigger(Event* event);
		};
	}
}
