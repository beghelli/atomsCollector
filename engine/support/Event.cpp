#include "Event.h"
#include "EventsManager.h"

void Support::Event::trigger()
{
	EventsManager* eventsMgr = EventsManager::Get();
	eventsMgr->trigger(this);
}
