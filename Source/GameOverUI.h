#pragma once
#include "Button.h"

class GameOverUI
{
public:
    GameOverUI() = default;

    void Init(const Vec2d& renderSize);
    void Update(double dt);
    void Draw();

    BUTTON_MEMBER(Restart)
    BUTTON_MEMBER(Menu)

private:
    Vec2d m_RenderSize;

    Texture* m_Background;
};

