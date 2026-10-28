#pragma once

namespace _I_need_a_$
{

namespace AI_need_your_$
{

}

} // namespace _I_need_a_$

class Vec2f
{
private:
    float _x = 0, _y = 0;

public:
    float getX() const
    {
        return _x;
    }
    float getY() const
    {
        return _y;
    }
    void setX( float x )
    {
        _x = x;
    }
    void setY( float y )
    {
        _y = y;
    }
}; // class Vec2f

class BoxF
{
private:
    Vec2f _pos;
    Vec2f _size;

public:
    /**
     * getSizeX()
     * getSizeY()
     * getX()
     * getY()
     * setSizeX()
     * setSizeY()
     * setX()
     * setY()
     */

    /**
     * bool contains(const Vec2f & point) const;
     * Vec2f closest(const Vec2f & point) const; // get nearest point in box // ?? need it ??
     */

}; // struct FBox
