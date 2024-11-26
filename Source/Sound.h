#pragma once
#include <string>

struct Mix_Chunk;

class Sound
{
public:
    Sound() = default;
    Sound(const std::string& filename);
    Sound(const Sound&) = delete;
    Sound(Sound&& other) noexcept;
    ~Sound();

    bool Load(const std::string& filename);
    Sound& operator=(const Sound&) = delete;
    Sound& operator=(Sound&& other) noexcept;

    Mix_Chunk* GetHandle() const;
    std::string GetFilename() const;

private:
    void Release();

    std::string m_Filename;
    Mix_Chunk* m_MixChunk;
};

