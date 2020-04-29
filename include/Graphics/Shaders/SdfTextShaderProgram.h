#pragma once
#include "GL/glew.h"
#include "Graphics/Shaders/ShaderProgram.h"

class SdfTextShaderProgram : public ShaderProgram
{
public:
	SdfTextShaderProgram(const char *vFilePath, const char *fFilePath);
	GLint mvpShLoc;
    GLint texRegionShLoc;
	GLint texSamplerShLoc;
	GLint paramsShLoc;
	GLint colorShLoc;
	GLint borderColorShLoc;
};

