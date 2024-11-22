#pragma once

#include "Vec2.h"

class GameObject
{
public:
    GameObject& operator=(const GameObject& other);

    virtual void Update(double dt) = 0;
    virtual void Draw() = 0;

    virtual void SetSize(const Vec2d& size);
    virtual Vec2d GetSize() const;

    bool IsIntersecting(const Vec2d& point) const;

    Vec2d Pos = {};
    double Angle = 0.0;

protected:
    Vec2d m_Size = {};
};

