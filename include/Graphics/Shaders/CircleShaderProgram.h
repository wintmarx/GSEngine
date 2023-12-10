#ifndef CIRCLE_SHADER_PROGRAM_HEADER
#define CIRCLE_SHADER_PROGRAM_HEADER

#include "Graphics/Shaders/ShaderProgram.h"

struct CircleShaderProgram : public ShaderProgram {
    GSENGINE_API CircleShaderProgram(const char* vFilePath, const char* fFilePath);
    GSENGINE_API ~CircleShaderProgram() override = default;
    GLint mvpShLoc;
    GLint colorShLoc;
    GLint innerRadiusShLoc;
};

#endif  // CIRCLE_SHADER_PROGRAM_HEADER
