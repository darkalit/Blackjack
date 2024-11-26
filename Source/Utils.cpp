#include "Utils.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::vector<std::string> Utils::ListFilesWithExtension(const std::string& path, const std::string& extension)
{
    std::vector<std::string> files;

    try
    {
        for (const auto& entry : fs::directory_iterator(path))
        {
            if (entry.is_regular_file() && entry.path().extension() == extension)
            {
                files.push_back(entry.path().string());
            }
        }
    } catch(const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    return files;
}
