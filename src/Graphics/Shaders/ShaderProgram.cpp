#define GSENGINE_EXPORT
#include "Graphics/Shaders/ShaderProgram.h"

#include <cstdio>
#include <vector>

#include "Graphics/GraphicsResources.h"
#include "FilesIO/FilesIO.h"

ShaderProgram::ShaderProgram()
{
	printf("Creating shader program\n");
	id = glCreateProgram();
	if (id > 0)
	{
		printf(" OK, id: %d\n", id);
	}
	else
	{
		printf(" Error\n");
	}
}

void ShaderProgram::Enable()
{
	if (id > 0)
	{
		glUseProgram(id);
	}
}

void ShaderProgram::Disable()
{
	glUseProgram(0);
}

ShaderProgram::~ShaderProgram()
{
	if (id > 0)
	{
		glDeleteProgram(id);
	}
}

std::string ShaderProgram::LoadShaderCode(GLuint sid, const char *fileName)
{
	std::string src;
	std::string path(GraphicsResources::shadersFolderPath);
	path.append(fileName);

	printf("Loading shader %d: %s\n", sid, fileName);

	uint8_t *buffer;
	size_t srcLength;
	if (!FilesIO::LoadBinaryFile(path, &buffer, srcLength))
	{
		return src;
	}
	src.append((char*)buffer, srcLength);
	delete[] buffer;

	return src;
}

bool ShaderProgram::CompileShader(GLuint sid, const std::string &src)
{
	printf("Compiling shader: %d\n", sid);

	GLint srcLen = src.size();

	const GLchar * srcData = src.data();
	glShaderSource(sid, 1, &srcData, (GLint*)&srcLen);
	glCompileShader(sid);

	GLint result = GL_FALSE;
	glGetShaderiv(sid, GL_COMPILE_STATUS, &result);
	if (result == GL_TRUE)
	{
		printf(" OK!\n");
		return true;
	}

	int InfoLogLength;
	glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> errorMessage(InfoLogLength + 1);
	glGetShaderInfoLog(sid, InfoLogLength, NULL, &errorMessage[0]);
	printf(" Error! [%s]\n", &errorMessage[0]);
	return false;
}

bool ShaderProgram::LoadShader(GLuint sid, const char *fileName)
{
	const std::string &src = LoadShaderCode(sid, fileName);
	return !src.empty() && CompileShader(sid, src);
}

bool ShaderProgram::AddShader(GLenum type, const char *fileName)
{
	printf("Adding Shader %s\n", fileName);
	if (id == 0)
	{
		printf(" Error! The program is not created.\n");
		return false;
	}
	GLuint sid = glCreateShader(type);
	if (sid == 0 || !LoadShader(sid, fileName))
	{
		glDeleteShader(sid);
		return false;
	}
	glAttachShader(id, sid);
	return true;
}

bool ShaderProgram::Link()
{
	printf("Linking shader program %d.\n", id);
	if (id == 0)
	{
		printf(" Error! The program is not created.\n");
		return false;
	}

	glLinkProgram(id);

	GLint result = GL_FALSE;
	glGetProgramiv(id, GL_LINK_STATUS, &result);
	if (result == GL_TRUE)
	{
		printf(" OK!\n");
		return true;	
	}
	int InfoLogLength;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
	glGetProgramInfoLog(id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	printf(" Error! [%s]\n", &ProgramErrorMessage[0]);
	return false;
}

GLint ShaderProgram::GetUniformLocation(const GLchar *name) const
{
	if (id == 0)
	{
		return 0;
	}
	return glGetUniformLocation(id, name);
}

GLuint ShaderProgram::CreateCompositeShader(GLenum type)
{
	GLuint sid;
	if ((sid = glCreateShader(type)) == 0)
	{
		return 0;
	}

	compositeShadersCodeBuffer.emplace(sid, std::string());
	return sid;
}

void ShaderProgram::AddPartialShaderFile(GLuint compositeShader, const char* fileName)
{
	auto it = compositeShadersCodeBuffer.find(compositeShader);
	if (it != compositeShadersCodeBuffer.end())
	{
		it->second.append("\n" + LoadShaderCode(compositeShader, fileName));
	}
}

void ShaderProgram::CompileCompositeShader(GLuint compositeShader)
{
	auto it = compositeShadersCodeBuffer.find(compositeShader);
	if (it != compositeShadersCodeBuffer.end())
	{
		CompileShader(compositeShader, it->second);
	}
	glAttachShader(id, compositeShader);
	compositeShadersCodeBuffer.erase(it);
}
