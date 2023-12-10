#define GSENGINE_EXPORT

#include "Graphics/Textures/Texture.h"

Texture::Texture(const std::string& filePath, uint32_t id, uint32_t width, uint32_t height)
    : id(id), width(width), height(height), filePath(filePath) {}

Texture::~Texture() = default;

bool Texture::IsEqualFilePath(const std::string& filePath) {
    return !this->filePath.compare(filePath);
}
