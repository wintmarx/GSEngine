#ifndef SPRITE_SHADER_PROGRAM_HEADER
#define SPRITE_SHADER_PROGRAM_HEADER

#include "Graphics/Shaders/ShaderProgram.h"

struct SpriteShaderProgram : public ShaderProgram {
    GSENGINE_API SpriteShaderProgram(const char* vFilePath, const char* fFilePath);
    GSENGINE_API ~SpriteShaderProgram() override = default;
    GLint mvpShLoc;
    GLint texRegionShLoc;
    GLint texSamplerShLoc;
    GLint matDiffColorShLoc;
    GLint isColoredShLoc;
};

#endif  // SPRITE_SHADER_PROGRAM_HEADER
