#ifndef GRAPHICS_LINE_HEADER
#define GRAPHICS_LINE_HEADER

#include <memory>

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "Graphics/Shaders/SpriteShaderProgram.h"
#include "LibExports.h"

class Line
{
public:
	GSENGINE_API Line();
	GSENGINE_API Line(const glm::vec3 &b, const glm::vec3 &e, float width, const glm::vec4 &color);
	GSENGINE_API ~Line();
	GSENGINE_API void Draw(const glm::mat4 &projection, const glm::mat4 &view);
	GSENGINE_API void SetLine(const glm::vec3 &b, const glm::vec3 &e, float width, const glm::vec4 &color);

private:
	float width = 1.f;
	static constexpr int vertexCount = 2;
	static constexpr int dim = 3;
	glm::vec4 color = glm::vec4(0.);
	GLuint vertexBuffer = 0;
	GLuint vertexArrayObject = 0;
	std::unique_ptr<SpriteShaderProgram> shaderProgram =
            std::make_unique<SpriteShaderProgram>("CommonSprite.vs", "CommonSprite.fs");
};

#endif
