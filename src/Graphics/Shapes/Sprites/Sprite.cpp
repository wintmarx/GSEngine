#define GSENGINE_EXPORT
#include "Graphics/Shapes/Sprites/Sprite.h"

#include <iostream>
#include <vector>

#include "glm/gtc/matrix_transform.hpp"

constexpr float defaultVbo[] =
        {
             0.5f,  0.5f, 0.f,    1.f, 1.f,
             0.5f, -0.5f, 0.f,    1.f, 0.f,
            -0.5f, -0.5f, 0.f,    0.f, 0.f,
            -0.5f,  0.5f, 0.f,    0.f, 1.f
        };

constexpr unsigned int defaultIndices[] = { 0, 1, 2, 0, 2, 3 };

Sprite::Sprite(const glm::vec3 &c)
{
	InitializeSprite();

	SetPosition(c);
}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Sprite::InitializeSprite()
{
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * (dim + 2), defaultVbo, GL_STATIC_DRAW);

	glVertexAttribPointer(0, dim, GL_FLOAT, GL_FALSE, sizeof(float) * (dim + 2), (void*)0);
    glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * (dim + 2), (void*)(sizeof(float) * dim));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), defaultIndices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Sprite::SetSize(float width, float height)
{
	Scale(glm::vec3(width/this->width, height/this->height, 1));
	this->width = width;
	this->height = height;
}

void Sprite::SetTextureShape(float uvX, float uvY, float width, float height)
{
	SetSize(width, height);
	int tW = this->texturesController->GetTextureWidth(this->textureId);
	int tH = this->texturesController->GetTextureHeight(this->textureId);
	textureRegion[0][0] = width / tW;
	textureRegion[1][1] = height / tH;
	textureRegion[2][0] = uvX / tW;
    textureRegion[2][1] = uvY / tH;
}

void Sprite::InvalidateModelMatrix()
{
    model = tM * rM * sM;
}

void Sprite::Rotate(const glm::vec3 &axis, float angle)
{
    rM = glm::rotate(rM, angle, axis);
    InvalidateModelMatrix();
}

void Sprite::SetAngle(const glm::vec3 &axis, float angle)
{
    rM = glm::rotate(glm::mat4(1), angle, axis);
    InvalidateModelMatrix();
}

void Sprite::Scale(const glm::vec3 &delta)
{
	sM = glm::scale(sM, delta);
    InvalidateModelMatrix();
}

void Sprite::SetScale(const glm::vec3 &scale)
{
    sM = glm::scale(glm::mat4(1), scale);
    InvalidateModelMatrix();
}

void Sprite::SetPosition(float x, float y, float z)
{
	tM[3].x = x;
	tM[3].y = y;
	tM[3].z = z;
    InvalidateModelMatrix();
}

void Sprite::SetPosition(const glm::vec3 &p)
{
	tM[3].x = p.x;
	tM[3].y = p.y;
	tM[3].z = p.z;
    InvalidateModelMatrix();
}

void Sprite::Translate(float dx, float dy, float dz)
{
	tM[3].x += dx;
	tM[3].y += dy;
	tM[3].z += dz;
    InvalidateModelMatrix();
}

void Sprite::Translate(const glm::vec3 &dPos)
{
	tM[3].x += dPos.x;
	tM[3].y += dPos.y;
	tM[3].z += dPos.z;
    InvalidateModelMatrix();
}

void Sprite::SetTexture(const char* filePath, bool isStdFolder)
{
	textureId = texturesController->AddTexture(filePath, isStdFolder);
	SetSize(texturesController->GetTextureWidth(textureId), texturesController->GetTextureHeight(textureId));
}

void Sprite::SetActiveShaderProgram(int localShaderProgramId)
{
	if (localShaderProgramId < 0)
	{
		std::cout << "Shader program id < 0";
		return;
	}
	currentShaderProgram = localShaderProgramId;
}

void Sprite::SetColor(const glm::vec4 &color)
{
	this->color = color;
}

TexturesController *Sprite::texturesController;
void Sprite::SetTexturesController(TexturesController *_texturesController)
{
	texturesController = _texturesController;
}


