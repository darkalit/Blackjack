#pragma once

#include <vector>

#include "Button.h"

class PauseUI
{
public:
    PauseUI() = default;

    void Init(const Vec2d& renderSize);
    void Update(double dt);
    void Draw();
    void SetButtonFunc(const std::function<std::function<void()>(const std::string&)>& func);

    BUTTON_MEMBER(Continue)
    BUTTON_MEMBER(Menu)

private:
    Vec2d m_RenderSize;

    std::function<std::function<void()>(const std::string& filename)> m_ButtonFunc;
    std::vector<Button> m_SkinButtons = {};

    Texture* m_Background;
};

