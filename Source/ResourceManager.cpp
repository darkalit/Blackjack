#include "ResourceManager.h"

#include "Texture.h"

std::unordered_map<std::string, Texture> ResourceManager::m_Textures = {};

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

Texture& ResourceManager::GetTexture(const std::string& filepath)
{
    return m_Textures.at(filepath);
}
