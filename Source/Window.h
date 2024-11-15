#pragma once

#include <string>

#include "Vec2.h"

struct SDL_Window;

class Window
{
public:
    enum WindowFlags : uint8_t
    {
        NONE = 0,
        FULLSCREEN,
        RESIZABLE,
    };

    Window(const std::string& title, const Vec2i& size, WindowFlags flags = NONE);
    ~Window();

    Vec2i GetSize() const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;
    void ToggleFullscreen();
        
    int32_t GetMouseX() const;
    int32_t GetMouseY() const;

    SDL_Window* GetHandle() const;

private:
    SDL_Window* m_Window = nullptr;
    Vec2i m_Size = {};
    bool m_Fullscreen = false;
};

