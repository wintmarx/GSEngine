#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>
#include "TextFont.h"
#include "LibExports.h"

struct OutputTextBlock
{
	uint32_t x;
	uint32_t y;
	std::string fontFilePath;
};

class TextBlock
{
public:
	GSENGINE_API TextBlock(std::string *text, int fontSize, glm::vec4 *color, float x, float y, TextFont *font);
	float x;
	float y;
	int fontSize;
	std::string text;
	std::string fontFilePath;
	std::vector<OutputTextBlock*> outputs;
	TextFont *font;
	glm::vec4 color;
};

