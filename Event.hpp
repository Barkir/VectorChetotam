#ifndef PHOTOSHOP_EVENT_HPP
#define PHOTOSHOP_EVENT_HPP

#include "utils/Vec2f.hpp"

enum class EventType
{
    mouse_down,
    mouse_up,
    mouse_move,
    key_pressed
};

struct MouseEvent
{
    Vec2f pos;
    int button = 0; // 0 - Left, 1 - Right
};

struct KeyboardEvent
{
    int key_code = 0;
    bool is_repeat = false;
};

struct Event
{
    EventType type;
    union
    {
        MouseEvent mouse;
        KeyboardEvent key;
    };

    Event() : type(EventType::mouse_move), mouse{} {}
    ~Event() = default;

    static Event createMouseEvent(EventType type, const Vec2f& pos, int button)
    {
        Event event{};
        event.type = type;
        event.mouse.pos = pos;
        event.mouse.button = button;
        return event;
    }

    static Event createKeyEvent(EventType type, int code, bool repeat)
    {
        Event event{};
        event.type = type;
        event.key.key_code = code;
        event.key.is_repeat = repeat;
        return event;
    }
};

#endif
