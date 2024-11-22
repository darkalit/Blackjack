#include "GameObject.h"

#include <cmath>
#include <iostream>

GameObject& GameObject::operator=(const GameObject& other)
{
    if (this == &other)
        return *this;
    Pos = other.Pos;
    Angle = other.Angle;
    m_Size = other.m_Size;
    return *this;
}

void GameObject::SetSize(const Vec2i& size)
{
    m_Size = size;
}

Vec2i GameObject::GetSize() const
{
    return m_Size;
}

bool GameObject::IsIntersecting(const Vec2d& point) const
{
    // As object is visually rotated, but coordinates of object is the same as non-rotated,
    // it needs to transform point coordinates to be rotated

    Vec2d center = { Pos.x + GetSize().x / 2.0, Pos.y + GetSize().y / 2.0 };
    Vec2d newPoint = { (point.x - center.x) * cos(Angle) + (point.y - center.y) * sin(Angle) + center.x, (point.x - center.x) * sin(Angle) - (point.y - center.y) * cos(Angle) + center.y};
    return newPoint.x < Pos.x + GetSize().x && newPoint.x > Pos.x && newPoint.y > Pos.y && newPoint.y < Pos.y + GetSize().y;
}
