#ifndef _MY_FBOX_HPP_
#define _MY_FBOX_HPP_

#include "utils/Vec2f.hpp"

struct BoxF
{
    Vec2f pos;
    Vec2f size;

    BoxF() = default;

    bool contains(const Vec2f& point) const
    {
        return point.x() >= pos.x() && point.x() <= pos.x() + size.x()
            && point.y() >= pos.y() && point.y() <= pos.y() + size.y();
    }

    BoxF(const Vec2f& pos1, const Vec2f& size1) : pos(pos1), size(size1) {}
};

#endif
