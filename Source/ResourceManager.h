#pragma once

#include <string>
#include <unordered_map>

class Texture;

class ResourceManager
{
public:
    ResourceManager() = delete;
    ~ResourceManager() = delete;

    static Texture& AddTexture(const std::string& filepath);
    static Texture& GetTexture(const std::string& filepath);

private:
    static std::unordered_map<std::string, Texture> m_Textures;
};

