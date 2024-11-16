#include "Texture.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Renderer.h"

Texture::Texture(const std::string& filename)
{
    Load(filename);
}

Texture::~Texture()
{
    Release();
}

bool Texture::Load(const std::string& filename)
{
    Release();

    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface)
    {
        std::cout << "Failed to load Texture::Surface: " << SDL_GetError();
        return false;
    }

    m_Texture = SDL_CreateTextureFromSurface(Renderer::GetHandle(), surface);
    if (!m_Texture)
    {
        std::cout << "Failed to load Texture::m_Texture: " << SDL_GetError();
        return false;
    }

    m_Size.x = surface->w;
    m_Size.y = surface->h;

    SDL_FreeSurface(surface);

    return m_Texture;
}

void Texture::SetColor(uint8_t r, uint8_t g, uint8_t b)
{
    SDL_SetTextureColorMod(m_Texture, r, g, b);
}

void Texture::SetAlpha(uint8_t a)
{
    SDL_SetTextureAlphaMod(m_Texture, a);
}

SDL_Texture* Texture::GetHandle() const
{
    return m_Texture;
}

Vec2i Texture::GetSize() const
{
    return m_Size;
}

int32_t Texture::GetWidth() const
{
    return m_Size.x;
}

int32_t Texture::GetHeight() const
{
    return m_Size.y;
}

void Texture::Release()
{
    if (m_Texture)
    {
        SDL_DestroyTexture(m_Texture);
        m_Texture = nullptr;
        m_Size = {};
    }
}
