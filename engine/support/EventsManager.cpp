#include <string>
#include <functional>
#include "EventsManager.h"

using namespace std;

Support::EventsManager* Support::EventsManager::eventsManager{nullptr};

Support::EventsManager* Support::EventsManager::Get()
{
	if (eventsManager == nullptr)
	{
		eventsManager = new Support::EventsManager();
	}

	return eventsManager;
}

void Support::EventsManager::listenFor(string event, function<void()> listenerFunction)
{
	EventListener listener;
	listener.event = event;
	listener.callback = listenerFunction;

	listeners.push_back(listener);
}

void Support::EventsManager::trigger(string event)
{
	for (EventListener listener : listeners)
	{
		if (listener.event != event)
		{
			continue;
		}

		listener.callback();
	}
}
