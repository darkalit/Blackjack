#pragma once

#include <string>
#include <unordered_map>

class Texture;
class Music;
class Sound;

class ResourceManager
{
public:
    ResourceManager() = delete;
    ~ResourceManager() = delete;

    static Texture& AddTexture(const std::string& filepath);
    static void RemoveTexture(const std::string& filepath);
    static Texture& GetTexture(const std::string& filepath);

    static Music& AddMusic(const std::string& filepath);
    static Music& GetMusic(const std::string& filepath);

    static Sound& AddSound(const std::string& filepath);
    static Sound& GetSound(const std::string& filepath);

private:
    static std::unordered_map<std::string, Texture> m_Textures;
    static std::unordered_map<std::string, Music> m_Musics;
    static std::unordered_map<std::string, Sound> m_Sounds;
};

