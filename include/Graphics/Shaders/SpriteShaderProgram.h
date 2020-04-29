#pragma once
#include "GL/glew.h"
#include "Graphics/Shaders/ShaderProgram.h"

class SpriteShaderProgram : public ShaderProgram
{
public:
	SpriteShaderProgram(const char *vFilePath, const char *fFilePath);
	GLint mvpShLoc;
	GLint texRegionShLoc;
	GLint texSamplerShLoc;
	GLint matDiffColorShLoc;
	GLint isColoredShLoc;
};

