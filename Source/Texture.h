#pragma once

#include <string>

#include "Vec2.h"

struct SDL_Texture;

class Texture
{
public:
    Texture() = default;
    Texture(const std::string& filename);
    Texture(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    ~Texture();

    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&& other) noexcept;

    bool Load(const std::string& filename);
    void SetColor(uint8_t r, uint8_t g, uint8_t b);
    void SetAlpha(uint8_t a);


    SDL_Texture* GetHandle() const;
    Vec2i GetSize() const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;
    std::string GetFilename() const;

private:
    void Release();

    std::string m_Filename;

    SDL_Texture* m_Texture = nullptr;

    Vec2i m_Size = {};
};

