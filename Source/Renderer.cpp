#include "Renderer.h"

#include <iostream>
#include <SDL.h>

#include "ResourceManager.h"
#include "Vec2.h"
#include "Texture.h"
#include "Window.h"

Texture* Renderer::s_NumTexture = nullptr;
SDL_Renderer* Renderer::s_Renderer = nullptr;

void Renderer::Init(const Window& window, const Vec2i& size)
{
    s_Renderer = SDL_CreateRenderer(window.GetHandle(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (!s_Renderer)
    {
        throw std::runtime_error(std::string("Failed to create SDL renderer: ") + SDL_GetError());
    }

    SDL_SetRenderDrawBlendMode(s_Renderer, SDL_BLENDMODE_BLEND);

    const char* hint = "SDL_HINT_RENDER_SCALE_QUALITY";
    if (!SDL_SetHintWithPriority(hint, "1", SDL_HINT_OVERRIDE))
    {
        std::cout << "Failed to set " << hint << " hint\n";
    }

    if (size != Vec2i{})
    {
        SDL_RenderSetLogicalSize(s_Renderer, size.x, size.y);
    }


    s_NumTexture = &ResourceManager::AddTexture("Assets/numbers.png");
}

void Renderer::Destroy()
{
    if (s_Renderer)
    {
        SDL_DestroyRenderer(s_Renderer);
    }
}

void Renderer::Clear()
{
    SDL_SetRenderDrawColor(s_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(s_Renderer);
}

void Renderer::Flush()
{
    SDL_RenderPresent(s_Renderer);
}

void Renderer::Draw(int32_t number, const Vec2i& pos)
{
    std::string numStr = std::to_string(number);
    for (int32_t i = 0; i < numStr.size(); ++i)
    {
        int32_t digit = numStr[i] - '0';

        SDL_Rect clip = { 11 * digit, 0, 11, 14 };
        Draw(*s_NumTexture, { 11 * i + pos.x, pos.y}, 0, &clip);
    }
}

void Renderer::Draw(const Texture& texture, const Vec2i& pos, double angle, SDL_Rect* clip)
{
    if (!texture.GetHandle())
        return;
    SDL_Rect rect = { pos.x, pos.y, texture.GetWidth(), texture.GetHeight() };
    if (clip)
    {
        rect.w = clip->w;
        rect.h = clip->h;
    }
    const double dAngle = angle * 180.0 / M_PI;

    SDL_RenderCopyEx(s_Renderer, texture.GetHandle(), clip, &rect, dAngle, nullptr, SDL_FLIP_NONE);
}

void Renderer::Draw(const Texture& texture, const Vec2i& pos, const Vec2i& size, double angle, const SDL_Rect* clip)
{
    if (!texture.GetHandle()) return;
    SDL_Rect rect = { pos.x, pos.y, size.x, size.y };
    const double dAngle = angle * 180.0 / M_PI;

    SDL_RenderCopyEx(s_Renderer, texture.GetHandle(), clip, &rect, dAngle, nullptr, SDL_FLIP_NONE);
}

void Renderer::Draw(const Texture& texture, const SDL_Rect* clip)
{
    if (!texture.GetHandle()) return;
    SDL_RenderCopyEx(s_Renderer, texture.GetHandle(), clip, nullptr, 0.0, nullptr, SDL_FLIP_NONE);
}

SDL_Renderer* Renderer::GetHandle()
{
    return s_Renderer;
}
