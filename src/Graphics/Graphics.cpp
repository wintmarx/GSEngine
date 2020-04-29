#define GSENGINE_EXPORT
#include "Graphics/Graphics.h"
#include <stdexcept>

Graphics::Graphics()
	: isInit((InitGLEW(), true)),
	  line(),
	  circle(),
	  texturesCtrl(std::make_unique<TexturesController>())
{
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);

	Sprite::SetTexturesController(texturesCtrl.get());
}

void Graphics::InitGLEW()
{
	glewExperimental = GL_TRUE;
	int ret;
	if ((ret = glewInit()) != GLEW_OK)
	{
		throw std::runtime_error("GLEW init error " + std::to_string(ret));
	}
}

void Graphics::DrawLine(const glm::vec3 &b, const glm::vec3 &e, float width, const glm::vec4 &color, const glm::mat4 &projection, const glm::mat4 &view) const
{
	line.SetLine(b, e, width, color);
	line.Draw(projection, view);
}

void Graphics::DrawCircle(const glm::vec3 &c, float radius, float width, const glm::vec4 &color, const glm::mat4 &projection, const glm::mat4 &view) const
{
	circle.SetCircle(c, radius, width, color);
	circle.Draw(projection, view);
}