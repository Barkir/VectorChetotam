#pragma once

class Vec2f
{
private:
    float _x = 0,
          _y = 0;

public:
    float getX() const { return _x; }
    float getY() const { return _y; }
    void setX(float x) { _x = x; }
    void setY(float y) { _y = y; }
}; // class Vec2f

struct FRect
{
    Vec2f _pos;
    Vec2f _size;
}; // struct Rect
