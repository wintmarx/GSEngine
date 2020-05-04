#ifndef SHADER_PROGRAM_HEADER
#define SHADER_PROGRAM_HEADER

#include <string>
#include <map>

#include "GL/glew.h"
#include "LibExports.h"

class ShaderProgram
{
public:
	GSENGINE_API ShaderProgram();
	GSENGINE_API void Enable();
	GSENGINE_API void Disable();
	GSENGINE_API bool AddShader(GLenum type, const char* fileName);
	GSENGINE_API bool Link();
	GSENGINE_API GLint GetUniformLocation(const GLchar* name) const;
	GSENGINE_API GLuint CreateCompositeShader(GLenum type);
	GSENGINE_API void AddPartialShaderFile(GLuint compositeShader, const char* fileName);
	GSENGINE_API void CompileCompositeShader(GLuint compositeShader);
	GSENGINE_API virtual ~ShaderProgram();
protected:
	GLuint id;
private:
	bool LoadShader(GLuint sid, const char *fileName);
	std::string LoadShaderCode(GLuint sid, const char *fileName);
	bool CompileShader(GLuint sid, const std::string &src);
	std::map<GLuint, std::string> compositeShadersCodeBuffer;
	std::map<GLuint, const char*> attachedShaders;
};

#endif
