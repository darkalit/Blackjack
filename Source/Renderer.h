#pragma once
#include <cstdint>
#include <string>

#include "Vec2.h"

struct SDL_Renderer;
struct SDL_Rect;
class Window;
class Texture;

class Renderer
{
public:
    Renderer() = delete;
    ~Renderer() = delete;

    static void Init(const Window& window, const Vec2i& size = {});
    static void Destroy();

    static void Clear();
    static void Flush();

    static void Draw(int32_t number, const Vec2i& pos);
    static void Draw(const Texture& texture, const Vec2i& pos, double angle = 0.0, SDL_Rect* clip = nullptr);
    static void Draw(const Texture& texture, const Vec2i& pos, const Vec2i& size, double angle = 0.0, const SDL_Rect* clip = nullptr);
    static void Draw(const Texture& texture, const SDL_Rect* clip = nullptr);

    static SDL_Renderer* GetHandle();

private:
    static Texture* s_NumTexture;
    static SDL_Renderer* s_Renderer;
};

