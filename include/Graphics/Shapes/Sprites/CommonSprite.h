#ifndef GSENGINE_COMMON_SPRITE
#define GSENGINE_COMMON_SPRITE

#include <vector>

#include "Sprite.h"

class SpriteShaderProgram;

class CommonSprite : public Sprite {
public:
    GSENGINE_API explicit CommonSprite(const glm::vec3& p);
    GSENGINE_API ~CommonSprite() override = default;
    GSENGINE_API void Draw(const glm::mat4& projection, const glm::mat4& view) override;
    GSENGINE_API void SetShader(const char* vFilePath, const char* fFilePath) override;
    GSENGINE_API void PrintInfo();

private:
    static std::vector<SpriteShaderProgram*> shaderPrograms;
};

#endif
