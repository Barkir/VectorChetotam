#ifndef PHOTOSHOP_EVENT_MANAGER_HPP
#define PHOTOSHOP_EVENT_MANAGER_HPP

class AObject;
struct Event;

class EventManager
{
public:
    // The root owns propagation through its children.
    bool dispatch(const Event& event, AObject& root) const;
};

#endif
