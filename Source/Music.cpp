#include "Music.h"

#include <iostream>
#include <SDL_mixer.h>

Music::Music(const std::string& filename)
{
    Load(filename);
}

Music::Music(Music&& other) noexcept
{
    m_MixMusic = other.m_MixMusic;
    other.m_MixMusic = nullptr;
    m_Filename = std::move(other.m_Filename);
}

Music::~Music()
{
    Release();
}

bool Music::Load(const std::string& filename)
{
    Release();

    m_Filename = filename;
    m_MixMusic = Mix_LoadMUS(filename.c_str());
    if (!m_MixMusic)
    {
        std::cout << "Failed to load Music: " << Mix_GetError();
        return false;
    }

    return m_MixMusic;
}

Music& Music::operator=(Music&& other) noexcept
{
    if (this != &other)
    {
        Release();
        std::swap(m_MixMusic, other.m_MixMusic);
        m_Filename = std::move(other.m_Filename);
    }

    return *this;
}

_Mix_Music* Music::GetHandle() const
{
    return m_MixMusic;
}

std::string Music::GetFilename() const
{
    return m_Filename;
}

void Music::Release()
{
    if (m_MixMusic)
    {
        Mix_FreeMusic(m_MixMusic);
        m_MixMusic = nullptr;
        m_Filename = "";
    }
}
