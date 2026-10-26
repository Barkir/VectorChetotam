#include "RaylibInputPump.hpp"

#include <raylib.h>

void RaylibInputPump::collectEvents()
{
    events_.clear();
    has_outstanding_event_ = false;

    const Vector2 mouse = GetMousePosition();
    const Vec2f mouse_pos{mouse.x, mouse.y};

    if (mouse_pos != previous_mouse_pos_)
        events_.push_back(Event::createMouseEvent(EventType::mouse_move, mouse_pos, 0));

    previous_mouse_pos_ = mouse_pos;

    for (int button = 0; button < 2; ++button)
    {
        const bool is_down = IsMouseButtonDown(button);

        if (is_down && !previous_mouse_buttons_[button])
            events_.push_back(Event::createMouseEvent(EventType::mouse_down, mouse_pos, button));
        else if (!is_down && previous_mouse_buttons_[button])
            events_.push_back(Event::createMouseEvent(EventType::mouse_up, mouse_pos, button));

        previous_mouse_buttons_[button] = is_down;
    }

    for (int key = GetKeyPressed(); key != 0; key = GetKeyPressed())
    {
        events_.push_back(Event::createKeyEvent(
            EventType::key_pressed, key, IsKeyPressedRepeat(key)));
    }
}

const Event* RaylibInputPump::pullEvent()
{
    if (has_outstanding_event_)
    {
        events_.pop_front();
        has_outstanding_event_ = false;
    }

    if (events_.empty())
        return nullptr;

    has_outstanding_event_ = true;
    return &events_.front();
}
