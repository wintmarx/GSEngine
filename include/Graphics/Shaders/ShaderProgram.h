#ifndef SHADER_PROGRAM_HEADER
#define SHADER_PROGRAM_HEADER

#include <map>
#include <string>

#include "GL/glew.h"
#include "LibExports.h"

class ShaderProgram {
public:
    GSENGINE_API ShaderProgram();
    GSENGINE_API virtual ~ShaderProgram();
    GSENGINE_API void Enable() const;
    GSENGINE_API void Disable() const;
    GSENGINE_API bool AddShader(GLenum type, std::string_view fileName) const;
    GSENGINE_API bool Link() const;
    GSENGINE_API GLint GetUniformLocation(std::string_view name) const;
    GSENGINE_API GLuint CreateCompositeShader(GLenum type);
    GSENGINE_API void AddPartialShaderFile(GLuint compositeShader, std::string_view fileName);
    GSENGINE_API void CompileCompositeShader(GLuint compositeShader);

private:
    static bool LoadShader(GLuint sid, std::string_view fileName);
    static std::string LoadShaderCode(GLuint sid, std::string_view fileName);
    static bool CompileShader(GLuint sid, std::string_view src);

protected:
    GLuint id;

private:
    std::map<GLuint, std::string> compositeShadersCodeBuffer;
    std::map<GLuint, const char*> attachedShaders;
};

#endif
