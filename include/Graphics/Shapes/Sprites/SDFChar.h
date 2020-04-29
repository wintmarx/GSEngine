#ifndef GSENGINE_SDF_CHAR
#define GSENGINE_SDF_CHAR

#include "Graphics/Shapes/Sprites/Sprite.h"
#include "Graphics/Shaders/SdfTextShaderProgram.h"
#include "LibExports.h"

class SDFChar :
	public Sprite
{
public:
	GSENGINE_API SDFChar(const glm::vec2 &drawParams);
	GSENGINE_API void Draw(const glm::mat4 &projection, const glm::mat4 &view);
	GSENGINE_API void SetShader(const char *vFilePath, const char *fFilePath);
	GSENGINE_API void SetBorder(const glm::vec4 &borderColor, const glm::vec2 &borderDrawParams);
	GSENGINE_API void DeleteBorder();
	GSENGINE_API void SetBorderParams(const glm::vec2 &params);
	GSENGINE_API void SetCharParams(const glm::vec2 &params);
	GSENGINE_API void SetParams(const glm::vec4 &params);
	GSENGINE_API void AddParams(const glm::vec4 &delta);
private:
	glm::vec4 borderColor;
	glm::vec4 params;
	static std::vector<SdfTextShaderProgram*> shaderPrograms;
};

#endif
