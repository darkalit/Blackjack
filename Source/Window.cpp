#include "Window.h"

#include <iostream>
#include <SDL.h>
#include <stdexcept>

Window::Window(const std::string& title, int32_t width, int32_t height, WindowFlags flags)
{
    uint32_t sdlFlags = 0;
    switch (flags)
    {
    case NONE:
        break;
    case FULLSCREEN:
        sdlFlags |= SDL_WINDOW_FULLSCREEN;
        m_Fullscreen = true;
        break;
    case RESIZABLE:
        sdlFlags |= SDL_WINDOW_RESIZABLE;
        break;
    }

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        throw std::runtime_error(std::string("Failed to init SDL video: ") + SDL_GetError());
    }

    m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, sdlFlags);

    if (!m_Window)
    {
        throw std::runtime_error(std::string("Failed to create SDL window: ") + SDL_GetError());
    }

    m_Width = width;
    m_Height = height;
}

Window::~Window()
{
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

int32_t Window::GetWidth() const
{
    return m_Width;
}

int32_t Window::GetHeight() const
{
    return m_Height;
}

void Window::ToggleFullscreen()
{
    int err = SDL_SetWindowFullscreen(m_Window, m_Fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    if (err < 0)
    {
        std::cout << "Failed to toggle fullscreen: " << SDL_GetError();
    } else
    {
        m_Fullscreen = !m_Fullscreen;
    }
}

int32_t Window::GetMouseX() const
{
    int p;
    SDL_GetMouseState(&p, nullptr);
    return p;
}

int32_t Window::GetMouseY() const
{
    int p;
    SDL_GetMouseState(nullptr, &p);
    return p;
}

SDL_Window* Window::GetHandle() const
{
    return m_Window;
}
