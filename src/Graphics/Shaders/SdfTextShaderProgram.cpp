#define GSENGINE_EXPORT

#include "Graphics/Shaders/SdfTextShaderProgram.h"

SdfTextShaderProgram::SdfTextShaderProgram(const char* vFilePath, const char* fFilePath)
    : ShaderProgram() {
    AddShader(GL_VERTEX_SHADER, vFilePath);
    AddShader(GL_FRAGMENT_SHADER, fFilePath);
    Link();
    mvpShLoc = glGetUniformLocation(id, "mvp");
    texRegionShLoc = glGetUniformLocation(id, "textureRegion");
    texSamplerShLoc = glGetUniformLocation(id, "tex");
    colorShLoc = glGetUniformLocation(id, "color");
    paramsShLoc = glGetUniformLocation(id, "params");
    borderColorShLoc = glGetUniformLocation(id, "borderColor");
}
