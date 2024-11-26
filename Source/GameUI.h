#pragma once

#include "Button.h"

class GameUI
{
public:
    GameUI() = default;

    void Init(const Vec2d& renderSize);
    void Update(double dt);
    void Draw(int32_t bet, int32_t cash);

    BUTTON_MEMBER(Pause)

    BUTTON_MEMBER(Hit)
    BUTTON_MEMBER(Stay)
    BUTTON_MEMBER(Start)

    BUTTON_MEMBER(5Bet)
    BUTTON_MEMBER(25Bet)
    BUTTON_MEMBER(100Bet)
    BUTTON_MEMBER(500Bet)

private:
    Texture* m_Navbar;
};
