#ifndef GSENGINE_COMMON_SPRITE
#define GSENGINE_COMMON_SPRITE

#include <vector>

#include "Sprite.h"
#include "Graphics/Shaders/SpriteShaderProgram.h"

class CommonSprite :
	public Sprite
{
public:
	GSENGINE_API CommonSprite(const glm::vec3 &p);
	GSENGINE_API void Draw(const glm::mat4 &projection, const glm::mat4 &view);
	GSENGINE_API void SetShader(const char *vFilePath, const char *fFilePath);
	GSENGINE_API void PrintInfo();
private:
	static std::vector<SpriteShaderProgram*> shaderPrograms;
};

#endif
