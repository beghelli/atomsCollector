#include <string>
#include <functional>
#include "EventsManager.h"
#include "Event.h"

using namespace std;
using namespace Engine::Support;

Engine::Support::EventsManager* Engine::Support::EventsManager::eventsManager{nullptr};

Engine::Support::EventsManager* Engine::Support::EventsManager::Get()
{
	if (eventsManager == nullptr)
	{
		eventsManager = new Engine::Support::EventsManager();
	}

	return eventsManager;
}

void Engine::Support::EventsManager::listenFor(string event, function<void(Event* event)> listenerFunction)
{
	EventListener listener;
	listener.event = event;
	listener.callback = listenerFunction;

	listeners.push_back(listener);
}

void Engine::Support::EventsManager::trigger(Event* event)
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
