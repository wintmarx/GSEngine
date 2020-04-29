#define GSENGINE_EXPORT
#include "Graphics/Textures/TexturesController.h"
#include <cstdio>
#include "GL/glew.h"
#include "Graphics/GraphicsResources.h"
#include "Graphics/Textures/PNGLoader.h"
#include "Graphics/Textures/TGALoader.h"

TexturesController::TexturesController()
{
	AddTexture("errorTexture.png");
}

uint32_t TexturesController::AddTexture(std::string filePath, bool isDefaultFolder)
{
	for (uint32_t i = 0; i < textures.size(); i++)
	{
		if (textures[i]->IsEqualFilePath(filePath))
		{
			return i + 1;
		}
	}

    if (isDefaultFolder)
    {
        filePath.insert(0, GraphicsResources::texturesFolderPath);
    }

	size_t dotPos = filePath.rfind('.');
	if (dotPos == std::string::npos)
	{
        printf("Image [%s] load error. Unsupported format\n", filePath.data());
		return 1;
	}

	std::vector<uint8_t> image;
	uint32_t width;
	uint32_t height;
	uint32_t error;
	int format;
	int internalFormat;
	if (!filePath.compare(dotPos + 1, 3, "png"))
	{
		error = lodepng::decode(image, width, height, filePath);
		if (error != 0)
		{
			printf("PNG image [%s] load error [%s]\n", filePath.data(), lodepng_error_text(error));
			return 1;
		}
		format = GL_RGBA;
		internalFormat = GL_RGBA;
	}
	else if (!filePath.compare(dotPos + 1, 3, "tga"))
	{
		error = LoadTGA(image, width, height, internalFormat, format, filePath);
		if (error != 0)
		{
            printf("TGA image [%s] load error [%d]\n", filePath.data(), error);
			return 1;
		}
	}
	else
	{
		printf("Image [%s] load error. Unsupported format\n", filePath.data());
		return 1;
	}

	GLuint textureId;

	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, &image[0]);

	printf("Texture loaded [%s]\n", filePath.data());
	textures.emplace_back(std::make_unique<Texture>(std::move(filePath), textureId, width, height));

	return textureId;
}

int TexturesController::GetTextureWidth(uint32_t textureId)
{
	return textureId - 1 < textures.size() ? textures[textureId - 1]->GetWidth() : 0;
}

int TexturesController::GetTextureHeight(uint32_t textureId)
{
	return textureId - 1 < textures.size() ? textures[textureId - 1]->GetHeight() : 0;
}


