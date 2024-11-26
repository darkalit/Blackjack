#pragma once

#include "Button.h"

class ResultsUI
{
public:
    enum class Outcome : uint8_t
    {
        WIN,
        BUST,
        PUSH,
        BLACKJACK,

        LAST = BLACKJACK,
    };

    ResultsUI() = default;

    void Init(const Vec2d& renderSize);
    void Update(double dt, Outcome outcome);
    void Draw();

    bool IsStarted();
    bool IsEnded();

    Vec2d Pos;

private:
    Outcome m_Outcome;
    Vec2d m_RenderSize;
    double m_T = 0.0;

    Texture* m_Banner;
    Texture* m_ResultsText;
};

