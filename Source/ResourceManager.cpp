#include "ResourceManager.h"

#include "Music.h"
#include "Sound.h"
#include "Texture.h"

std::unordered_map<std::string, Texture> ResourceManager::m_Textures = {};
std::unordered_map<std::string, Music> ResourceManager::m_Musics = {};
std::unordered_map<std::string, Sound> ResourceManager::m_Sounds = {};

Texture& ResourceManager::AddTexture(const std::string& filepath)
{
    auto pair = m_Textures.find(filepath);
    if (pair != m_Textures.end())
    {
        return pair->second;
    }

    auto texture = Texture(filepath);
    m_Textures.try_emplace(filepath, std::move(texture));

    return m_Textures.at(filepath);
}

void ResourceManager::RemoveTexture(const std::string& filepath)
{
    auto pair = m_Textures.find(filepath);
    if (pair != m_Textures.end())
    {
        m_Textures.erase(pair);
    }
}

Texture& ResourceManager::GetTexture(const std::string& filepath)
{
    return m_Textures.at(filepath);
}

Music& ResourceManager::AddMusic(const std::string& filepath)
{
    auto pair = m_Musics.find(filepath);
    if (pair != m_Musics.end())
    {
        return pair->second;
    }

    auto music = Music(filepath);
    m_Musics.try_emplace(filepath, std::move(music));

    return m_Musics.at(filepath);
}

Music& ResourceManager::GetMusic(const std::string& filepath)
{
    return m_Musics.at(filepath);
}

Sound& ResourceManager::AddSound(const std::string& filepath)
{
    auto pair = m_Sounds.find(filepath);
    if (pair != m_Sounds.end())
    {
        return pair->second;
    }

    auto sound = Sound(filepath);
    m_Sounds.try_emplace(filepath, std::move(sound));

    return m_Sounds.at(filepath);
}

Sound& ResourceManager::GetSound(const std::string& filepath)
{
    return m_Sounds.at(filepath);
}
