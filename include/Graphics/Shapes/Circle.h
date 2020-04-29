#ifndef GRAPHICS_CIRCLE_HEADER
#define GRAPHICS_CIRCLE_HEADER

#include "Graphics/Shapes/Sprites/Sprite.h"
#include "Graphics/Shaders/CircleShaderProgram.h"
#include "glm/glm.hpp"

class Circle : public Sprite
{
public:
	GSENGINE_API Circle();
	GSENGINE_API Circle(const glm::vec3 &c, float radius, float width, const glm::vec4 &color);
	GSENGINE_API ~Circle() = default;
	GSENGINE_API void Draw(const glm::mat4 &projection, const glm::mat4 &view);
	GSENGINE_API void SetCircle(const glm::vec3 &c, float radius, float width, const glm::vec4 &color);
	GSENGINE_API void SetShader(const char *vFilePath, const char *fFilePath);

private:
	float innerRadius = 0.f;
	std::unique_ptr<CircleShaderProgram> shaderProgram =
	        std::make_unique<CircleShaderProgram>("circle.vs", "circle.fs");
};

#endif