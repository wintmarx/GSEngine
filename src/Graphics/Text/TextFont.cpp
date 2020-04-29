#define GSENGINE_EXPORT
#include "Graphics/Text/TextFont.h"

#include <stdio.h>
#include <vector>
#include <fstream>

void TextFont::DrawText(const std::wstring &text, float size, const glm::vec4 &color, float x, float y, const glm::mat4 &projection)
{
	scale.x = size / fontSize;
	scale.y = scale.x;
	scale.z = 1.f;
	sprite->Scale(scale);
	sprite->SetPosition(x, y, 0);
    sprite->SetColor(color);
	for (uint32_t i = 0, j = 0; i < text.size(); i++)
	{
		if (text[i] == L'\n')
		{
			sprite->Translate(0, -size, 0);
			continue;
		}
		j = 1 + (text[i] > 1000 ? (text[i] - 945 ) : (text[i] - 32));
		sprite->Translate((glyphs[j].width * 0.5f + glyphs[j].xOffset) * scale.x,
		                  (glyphs[j].height * 0.5f + glyphs[j].yOffset) * (-scale.y), 0);

		sprite->SetTextureShape(glyphs[j].x, glyphs[j].y, glyphs[j].width, glyphs[j].height);
		sprite->Draw(projection, glm::mat4(1));

		sprite->Translate((glyphs[j].xAdvance - glyphs[j].xOffset - glyphs[j].width * 0.5f) * scale.x,
                          (glyphs[j].yOffset + glyphs[j].height * 0.5f) * scale.y, 0);
	}
	scale.x = 1.f / scale.x;
	scale.y = 1.f / scale.y;
	sprite->Scale(scale);
}


TextFont::TextFont(const char* filePath)
{
	LoadFont(filePath);
}

void TextFont::ShowInfo()
{
	printf("\nTexture size:%fx%f", sprite->width, sprite->height);
	for (unsigned int i = 0; i < glyphs.size(); i++)
	{
		printf("\nGlyph %d id:%d, x:%d, y:%d, w:%d, h:%d", i, glyphs[i].id, glyphs[i].x, glyphs[i].y, glyphs[i].width, glyphs[i].height);
	}
}

void TextFont::AddParamValue(const glm::vec4 &delta)
{
	sprite->AddParams(delta);
}

void TextFont::SetParamValue(const glm::vec4 &params)
{
	sprite->SetParams(params);
}

void TextFont::LoadFont(const std::string &filePath)
{
	uint32_t headerSize = 5;
	uint8_t *buffer;
	size_t size;
	this->filePath = filePath;

	if (!FilesIO::LoadBinaryFile(filePath.data(), &buffer, size))
	{
		printf("Loading font error\n");
		return;
	}
	std::unique_ptr<uint8_t[]> raiiBuf(buffer);

	uint32_t infoBlockLength = *(uint32_t*)(buffer + headerSize);
	uint32_t commonBlockOffset = headerSize + 5 + infoBlockLength;
	uint32_t commonBlockLength = *(uint32_t*)(buffer + commonBlockOffset);
	uint32_t pagesBlockOffset = commonBlockOffset + 5 + commonBlockLength;
	uint32_t pagesBlockLength = *(uint32_t*)(buffer + pagesBlockOffset);
	uint32_t charsBlockOffset = pagesBlockOffset + 5 + pagesBlockLength;
	uint32_t charsBlockLength = *(uint32_t*)(buffer + charsBlockOffset);

	fontSize = abs(*(int16_t*)(buffer + headerSize + 4))/8;
	lineHeight = (*(uint16_t*)(buffer + commonBlockOffset + 4))/8;
	base = (*(uint16_t*)(buffer + commonBlockOffset + 4 + 2))/8;
	name = std::string((char*)(buffer + headerSize + 5 + 13), infoBlockLength - 14);

    size_t b = filePath.rfind('/');
	std::string textureFileName =
	        filePath.substr(0, (b? (b + 1) : 0)) +
	        std::string((char*)(buffer + pagesBlockOffset + 4), pagesBlockLength);

	sprite = std::make_unique<SDFChar>(glm::vec2(0.0, 50));
	sprite->SetShader("SDFText.vs", "SDFText.fs");
	sprite->SetTexture(textureFileName.data(), false);
	sprite->SetBorder(glm::vec4(1, 1, 0, 1), glm::vec2(0.5, 50));

	b = charsBlockLength / 20;
	glyphs.reserve(b);
	for (uint32_t i = 0; i < b; i++)
	{
	    glyphs.push_back(*(Glyph*)(buffer + charsBlockOffset + 4 + i * 20));
		glyphs[i].height /= 8;
		glyphs[i].width /= 8;
		glyphs[i].x /= 8;
		glyphs[i].y /= 8;
		glyphs[i].xOffset /= 8;
		glyphs[i].yOffset /= 8;
		glyphs[i].xAdvance /= 8;
	}
}

std::string TextFont::GetFilePath()
{
	return filePath;
}
