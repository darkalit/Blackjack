#include "Renderer.h"

#include <iostream>
#include <SDL.h>

#include "Vec2.h"
#include "Texture.h"
#include "Window.h"

SDL_Renderer* Renderer::m_Renderer = nullptr;

void Renderer::Init(const Window& window, const Vec2i& size)
{
    m_Renderer = SDL_CreateRenderer(window.GetHandle(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (!m_Renderer)
    {
        throw std::runtime_error(std::string("Failed to create SDL renderer: ") + SDL_GetError());
    }

    SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);

    const char* hint = "SDL_HINT_RENDER_SCALE_QUALITY";
    if (!SDL_SetHintWithPriority(hint, "1", SDL_HINT_OVERRIDE))
    {
        std::cout << "Failed to set " << hint << " hint\n";
    }

    if (size != Vec2i{})
    {
        SDL_RenderSetLogicalSize(m_Renderer, size.x, size.y);
    }
}

void Renderer::Destroy()
{
    if (m_Renderer)
    {
        SDL_DestroyRenderer(m_Renderer);
    }
}

void Renderer::Clear()
{
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);
}

void Renderer::Flush()
{
    SDL_RenderPresent(m_Renderer);
}

void Renderer::Draw(const Texture& texture, const Vec2i& pos, double angle, SDL_Rect* clip)
{
    SDL_Rect rect = { pos.x, pos.y, texture.GetWidth(), texture.GetHeight() };
    if (clip)
    {
        rect.w = clip->w;
        rect.h = clip->h;
    }
    const double dAngle = angle * 180.0 / M_PI;

    SDL_RenderCopyEx(m_Renderer, texture.GetHandle(), clip, &rect, dAngle, nullptr, SDL_FLIP_NONE);
}

void Renderer::Draw(const Texture& texture, const Vec2i& pos, const Vec2i& size, double angle, const SDL_Rect* clip)
{
    SDL_Rect rect = { pos.x, pos.y, size.x, size.y };
    const double dAngle = angle * 180.0 / M_PI;

    SDL_RenderCopyEx(m_Renderer, texture.GetHandle(), clip, &rect, dAngle, nullptr, SDL_FLIP_NONE);
}

void Renderer::Draw(const Texture& texture, const SDL_Rect* clip)
{
    SDL_RenderCopyEx(m_Renderer, texture.GetHandle(), clip, nullptr, 0.0, nullptr, SDL_FLIP_NONE);
}

SDL_Renderer* Renderer::GetHandle()
{
    return m_Renderer;
}
