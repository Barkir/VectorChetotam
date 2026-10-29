#ifndef PHOTOSHOP_EVENT_HPP
#define PHOTOSHOP_EVENT_HPP

#include "SDK/Utils/Vec2F.hpp"

enum class EventType
{
    MOUSE_DOWN,
    MOUSE_UP,
    MOUSE_MOVE,
    KEY_PRESSED,
};

enum class MouseButton
{
    LEFT,
    RIGHT,
    MIDDLE,
};

enum class KeyCode
{
    UNKNOWN,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    DIGIT_0,
    DIGIT_1,
    DIGIT_2,
    DIGIT_3,
    DIGIT_4,
    DIGIT_5,
    DIGIT_6,
    DIGIT_7,
    DIGIT_8,
    DIGIT_9,
    SPACE,
    ESCAPE,
    ENTER,
    TAB,
    BACKSPACE,
    DELETE_KEY,
    INSERT,
    HOME,
    END,
    PAGE_UP,
    PAGE_DOWN,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    SHIFT_LEFT,
    SHIFT_RIGHT,
    CONTROL_LEFT,
    CONTROL_RIGHT,
    ALT_LEFT,
    ALT_RIGHT,
    META_LEFT,
    META_RIGHT,
    CAPS_LOCK,
    NUM_LOCK,
    SCROLL_LOCK,
    PRINT_SCREEN,
    PAUSE,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    GRAVE,
    MINUS,
    EQUAL,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    BACKSLASH,
    SEMICOLON,
    APOSTROPHE,
    COMMA,
    PERIOD,
    SLASH,
};

// Реализуйте в адаптере выбранной графической библиотеки: сопоставьте её коды
// клавиш с KeyCode через switch и верните UNKNOWN для неподдерживаемых клавиш.
namespace Input
{

KeyCode convertKey(int library_key);

}

struct MouseEvent
{
    Vec2F       pos;
    MouseButton button = MouseButton::LEFT;
};

struct KeyboardEvent
{
    KeyCode key_code  = KeyCode::UNKNOWN;
    bool    is_repeat = false;
};

struct Event
{
    EventType type;
    union
    {
        MouseEvent    mouse;
        KeyboardEvent key;
    };

    Event() : type(EventType::MOUSE_MOVE), mouse{}
    {
    }
    ~Event() = default;

    static Event createMouseEvent(EventType type, const Vec2F& pos, MouseButton button)
    {
        Event event{};
        event.type         = type;
        event.mouse.pos    = pos;
        event.mouse.button = button;
        return event;
    }

    static Event createKeyEvent(EventType type, KeyCode code, bool repeat)
    {
        Event event{};
        event.type          = type;
        event.key.key_code  = code;
        event.key.is_repeat = repeat;
        return event;
    }
};

#endif
