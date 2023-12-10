#ifndef GSENGINE_TEXTURE_CONTROLLER
#define GSENGINE_TEXTURE_CONTROLLER

#include <memory>
#include <string>
#include <vector>

#include "LibExports.h"

class Texture;

class TexturesController {
public:
    GSENGINE_API TexturesController();
    GSENGINE_API ~TexturesController();
    GSENGINE_API uint32_t AddTexture(std::string filePath, bool isDefaultFolder = true);
    GSENGINE_API int GetTextureWidth(uint32_t textureId);
    GSENGINE_API int GetTextureHeight(uint32_t textureId);

private:
    std::vector<std::unique_ptr<Texture>> textures;
};

#endif
