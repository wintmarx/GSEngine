#pragma once

#include <string>

#include "LibExports.h"

class Texture {
public:
    GSENGINE_API Texture(const std::string& filePath, uint32_t id, uint32_t width, uint32_t height);
    GSENGINE_API ~Texture();
    GSENGINE_API bool IsEqualFilePath(const std::string& filePath);
    GSENGINE_API uint32_t GetId() { return id; }
    GSENGINE_API uint32_t GetWidth() { return width; }
    GSENGINE_API uint32_t GetHeight() { return height; }

private:
    uint32_t id;
    uint32_t width;
    uint32_t height;
    std::string filePath;
};
