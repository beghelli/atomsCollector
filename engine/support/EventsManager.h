#pragma once
#include <functional>
#include <vector>
#include <string>

using namespace std;

namespace Support
{
	typedef struct EventListener {
		string event;
		function<void()> callback;
	} EventListener;

	class EventsManager
	{
		private:
			static EventsManager* eventsManager;
			vector<EventListener> listeners;

		public:
			static EventsManager* Get();
			void listenFor(string event, function<void()> listenerFunction);
			void trigger(string event);
	};
}
