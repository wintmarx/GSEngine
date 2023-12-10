#ifndef SDF_TEXT_SHADER_PROGRAM_HEADER
#define SDF_TEXT_SHADER_PROGRAM_HEADER

#include "Graphics/Shaders/ShaderProgram.h"

struct SdfTextShaderProgram : public ShaderProgram {
    GSENGINE_API SdfTextShaderProgram(const char* vFilePath, const char* fFilePath);
    GSENGINE_API ~SdfTextShaderProgram() override = default;
    GLint mvpShLoc;
    GLint texRegionShLoc;
    GLint texSamplerShLoc;
    GLint paramsShLoc;
    GLint colorShLoc;
    GLint borderColorShLoc;
};

#endif  // SDF_TEXT_SHADER_PROGRAM_HEADER
