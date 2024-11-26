#pragma once
#include <string>

struct _Mix_Music;

class Music
{
public:
    Music() = default;
    Music(const std::string& filename);
    Music(const Music&) = delete;
    Music(Music&& other) noexcept;
    ~Music();

    bool Load(const std::string& filename);
    Music& operator=(const Music&) = delete;
    Music& operator=(Music&& other) noexcept;

    _Mix_Music* GetHandle() const;
    std::string GetFilename() const;

private:
    void Release();

    std::string m_Filename;
    _Mix_Music* m_MixMusic;
};

