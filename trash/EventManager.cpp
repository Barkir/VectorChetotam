#include "EventManager.hpp"

#include "App.hpp"

bool EventManager::dispatch(const Event& event, AObject& root) const
{
    return root.processEvent(event);
}
