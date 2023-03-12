#include <string>
#include <functional>
#include "EventsManager.h"
#include "Event.h"

using namespace std;
using namespace Support;

Support::EventsManager* Support::EventsManager::eventsManager{nullptr};

Support::EventsManager* Support::EventsManager::Get()
{
	if (eventsManager == nullptr)
	{
		eventsManager = new Support::EventsManager();
	}

	return eventsManager;
}

void Support::EventsManager::listenFor(string event, function<void(Event* event)> listenerFunction)
{
	EventListener listener;
	listener.event = event;
	listener.callback = listenerFunction;

	listeners.push_back(listener);
}

void Support::EventsManager::trigger(Event* event)
{
	for (EventListener listener : listeners)
	{
		if (listener.event != event->id)
		{
			continue;
		}

		listener.callback(event);
	}
}
