#include "Button.h"

#include <SDL_rect.h>

#include "Input.h"
#include "Renderer.h"

void Button::Init(Texture& texture, const Vec2d& pos)
{
    m_Texture = &texture;
    Pos = pos;
}

void Button::Update(double dt)
{
    Vec2d cursor = { Input::GetKeyIsCalled(InputKey::MOUSE_X), Input::GetKeyIsCalled(InputKey::MOUSE_Y) };

    if (IsIntersecting(cursor) && Input::GetKeyIsCalled(InputKey::MOUSE_LB, KeyActivation::ON_START))
    {
        m_Held = true;
        OnPress();
    }

    if (!Input::GetKeyIsCalled(InputKey::MOUSE_LB, KeyActivation::HOLD))
    {
        m_Held = false;
    }
}

void Button::Draw()
{
    SDL_Rect iconClip = { 0, 0, static_cast<int32_t>(GetSize().x), static_cast<int32_t>(GetSize().y) };

    if (!m_Held)
    {
        SDL_Rect buttonClip = { static_cast<int32_t>(GetSize().x), 0, static_cast<int32_t>(GetSize().x), static_cast<int32_t>(GetSize().y) };
        Renderer::Draw(*m_Texture, Pos, GetSize(), Angle, &buttonClip);
    } else
    {
        SDL_Rect buttonClip = { static_cast<int32_t>(GetSize().x) * 2, 0, static_cast<int32_t>(GetSize().x), static_cast<int32_t>(GetSize().y) };
        Renderer::Draw(*m_Texture, Pos, GetSize(), Angle, &buttonClip);
    }
    Renderer::Draw(*m_Texture, Pos, GetSize(), Angle, &iconClip);
}

Vec2d Button::GetSize() const
{
    if (m_Size == Vec2i{} && m_Texture)
    {
        return { m_Texture->GetSize().x / 3, m_Texture->GetSize().y };
    }
    return m_Size;    
}
