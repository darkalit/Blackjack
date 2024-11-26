#pragma once

#include "Button.h"

class MenuUI
{
public:
    MenuUI() = default;

    void Init(const Vec2d& renderSize);
    void Update(double dt);
    void Draw();

    BUTTON_MEMBER(Start)
    BUTTON_MEMBER(Exit)

private:
    Texture* m_Background;
};

