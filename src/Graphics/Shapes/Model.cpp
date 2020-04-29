#define GSENGINE_EXPORT

#include <iostream>
#include <vector>
#include <fstream>

#include "Graphics/Shapes/Model.h"

Model::Model(const std::string &filePath, GLuint shadingProgramId)
{
	LoadModel(filePath);
	AddShader(shadingProgramId);
}

Model::Model()
{

}

Model::~Model()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &textureBuffer);
}

void SplitLine(std::string line, int *count, float *arr)
{
	std::string buff = "";
	for (unsigned int i = 2; i < line.length(); i++)
	{
		if (line[i] == ' ')
		{
			if (buff != "")
			{
				arr[*count] = stof(buff);
				(*count)++;
				buff = "";
			}
			continue;
		}
		buff += line[i];
	}
	if (buff != "")
	{
		arr[*count] = stof(buff);
		(*count)++;
		buff = "";
	}
}

void Model::LoadModel(std::string filePath)
{
	std::fstream fileStream;
	std::string line = "";
	vCoordCount = 0;
	tCoordCount = 0;
	nCoordCount = 0;
	indexCount = 0;
	float* vCoords = nullptr;
	float* tCoords = nullptr;
	unsigned int* indices = nullptr;
	float *nCoords = nullptr;
	std::string tmp = "";
	fileStream.open(filePath, std::ios::in);
	if (!fileStream.is_open())
	{
        printf("Can not open %s.\n", filePath.c_str());
        return;
    }
	while (std::getline(fileStream, line))
	{
		switch (line[0])
		{
		case 'v':
			SplitLine(line, &vCoordCount, vCoords);
			break;
		case 'i':
			for (unsigned int i = 2; i < line.length(); i++)
			{
				if (line[i] == ' ')
				{
					if (tmp != "")
					{
						indices[indexCount] = stoi(tmp);
						indexCount++;
						tmp = "";
					}
					continue;
				}
				tmp += line[i];
			}
			if (tmp != "")
			{
				indices[indexCount] = stoi(tmp);
				indexCount++;
				tmp = "";
			}
			break;
		case 'n':
			SplitLine(line, &nCoordCount, nCoords);
			break;
		case 't':
			SplitLine(line, &tCoordCount, tCoords);
			break;
		}
	}
	fileStream.close();

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vCoordCount, vCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nCoordCount, nCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tCoordCount, tCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vertexShaderBuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertexShaderBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * vCoordCount, vCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	textureId = -1;
	alphaId = -1;
}

void Model::AddShader(GLuint shadingProgramId)
{
	shadingProgramID = shadingProgramId;
	mvpShLoc = glGetUniformLocation(shadingProgramID, "MVP");
	mShLoc = glGetUniformLocation(shadingProgramID, "M");
	vShLoc = glGetUniformLocation(shadingProgramID, "V");

	lightPosShLoc = glGetUniformLocation(shadingProgramID, "lightPositionW");
	lightColorShLoc = glGetUniformLocation(shadingProgramID, "lightColor");
	lightPowerShLoc = glGetUniformLocation(shadingProgramID, "lightPower");

	matSpecColorShLoc = glGetUniformLocation(shadingProgramID, "materialSpecularColor");
	matDiffColorShLoc = glGetUniformLocation(shadingProgramID, "materialDiffuseColor");
	matAmbColorShLoc = glGetUniformLocation(shadingProgramID, "materialAmbientColor");

	texSamplerShLoc = glGetUniformLocation(shadingProgramID, "textureSampler");
	alphaSamplerShLoc = glGetUniformLocation(shadingProgramID, "alphaSampler");
}


void Model::Draw(const glm::mat4 &model, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &lightPos)
{
	glUseProgram(shadingProgramID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, alphaId);

	glUniformMatrix4fv(mvpShLoc, 1, GL_FALSE, &(projection * view * model)[0][0]);
	glUniformMatrix4fv(vShLoc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(mShLoc, 1, GL_FALSE, &model[0][0]);

	glUniform3fv(matDiffColorShLoc, 1, &diffColor[0]);
	glUniform3fv(matSpecColorShLoc, 1, &specColor[0]);
	glUniform3fv(matAmbColorShLoc, 1, &ambColor[0]);

	glUniform3fv(lightPosShLoc, 1, &lightPos[0]);
	glUniform3fv(lightColorShLoc, 1, &lightColor[0]);
	glUniform1f(lightPowerShLoc, lightPower);

	glUniform1i(texSamplerShLoc, 0);
	glUniform1i(alphaSamplerShLoc, 1);

	//glEnableVertexAttribArray(0);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, vertexShaderBuffer);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void Model::AddTexture(GLuint textureId)
{
	if (this->textureId != 0)
		this->alphaId = textureId;
	else
		this->textureId = textureId;
}