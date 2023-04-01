#include "Event.h"
#include "EventsManager.h"

void Engine::Support::Event::trigger()
{
	EventsManager* eventsMgr = EventsManager::Get();
	eventsMgr->trigger(this);
}
