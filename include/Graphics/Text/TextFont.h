#ifndef GSENGINE_TEXTFONT
#define GSENGINE_TEXTFONT

#include <string>
#include <vector>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "Graphics/Shaders/SdfTextShaderProgram.h"
#include "Graphics/Shapes/Sprites/SDFChar.h"
#include "FilesIO/FilesIO.h"

struct Glyph
{
	uint32_t id;
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
	int16_t xOffset;
	int16_t yOffset;
	int16_t xAdvance;
};

class TextFont
{
public:
	GSENGINE_API void DrawText(const std::wstring &text, float size, const glm::vec4 &color, float x, float y, const glm::mat4 &projection);
	GSENGINE_API TextFont(const char* filePath);
	GSENGINE_API ~TextFont() = default;
	GSENGINE_API void AddParamValue(const glm::vec4 &delta);
	GSENGINE_API void SetParamValue(const glm::vec4 &params);
	GSENGINE_API std::string GetFilePath();
	GSENGINE_API void ShowInfo();
private:
	void LoadFont(const std::string &filePath);
	std::vector<Glyph> glyphs;
	std::unique_ptr<SDFChar> sprite;
	int16_t fontSize = 0;
	uint16_t lineHeight = 0;
	uint16_t base = 0;
	glm::vec3 scale{ 1.f };
	std::string name;
	std::string filePath;
	
};

#endif
