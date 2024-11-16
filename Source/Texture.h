#pragma once

#include <string>

#include "Vec2.h"

struct SDL_Texture;

enum class BlendMode {
    NONE,
    BLEND,
    ADD,
    MOD,
    MUL,
};

class Texture
{
public:
    Texture() = default;
    Texture(const std::string& filename);
    ~Texture();

    bool Load(const std::string& filename);
    void SetColor(uint8_t r, uint8_t g, uint8_t b);
    void SetAlpha(uint8_t a);


    SDL_Texture* GetHandle() const;
    Vec2i GetSize() const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;

private:
    void Release();

    SDL_Texture* m_Texture = nullptr;

    Vec2i m_Size = {};
};

