#include "Sound.h"

#include <iostream>
#include <SDL_mixer.h>

Sound::Sound(const std::string& filename)
{
    Load(filename);
}

Sound::Sound(Sound&& other) noexcept
{
    m_MixChunk = other.m_MixChunk;
    other.m_MixChunk = nullptr;
    m_Filename = std::move(other.m_Filename);
}

Sound::~Sound()
{
    Release();
}

bool Sound::Load(const std::string& filename)
{
    Release();

    m_Filename = filename;
    m_MixChunk = Mix_LoadWAV(filename.c_str());
    if (!m_MixChunk)
    {
        std::cout << "Failed to load Sound: " << Mix_GetError();
        return false;
    }

    return m_MixChunk;
}

Sound& Sound::operator=(Sound&& other) noexcept
{
    if (this != &other)
    {
        Release();
        std::swap(m_MixChunk, other.m_MixChunk);
        m_Filename = std::move(other.m_Filename);
    }

    return *this;
}

Mix_Chunk* Sound::GetHandle() const
{
    return m_MixChunk;
}

std::string Sound::GetFilename() const
{
    return m_Filename;
}

void Sound::Release()
{
    if (m_MixChunk)
    {
        Mix_FreeChunk(m_MixChunk);
        m_MixChunk = nullptr;
        m_Filename = "";
    }
}
