#ifndef GSENGINE_MODEL
#define GSENGINE_MODEL

#include <string>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "LibExports.h"

class Model
{
public:
	GSENGINE_API Model(const std::string &filePath, GLuint shadingProgramId);
	GSENGINE_API Model();
	GSENGINE_API ~Model();
	GSENGINE_API void Draw(const glm::mat4 &model, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &lightPos);
	GSENGINE_API void AddTexture(GLuint textureId);
	GSENGINE_API int GetVerticesCount() { return vCoordCount/3; }
	GSENGINE_API GLuint GetVerticesBuffer() { return vertexShaderBuffer; }
private:
    void LoadModel(std::string filePath);
    void AddShader(GLuint shadingProgramId);

	GLuint vertexBuffer;
	GLuint vertexShaderBuffer;
	GLuint indexBuffer;
	GLuint normalBuffer;
	GLuint textureBuffer;
	GLuint textureId;
	GLuint alphaId;
	int vCoordCount;
	int nCoordCount;
	int tCoordCount;
	int indexCount;

	GLuint shadingProgramID;
	GLint mvpShLoc;
	GLint mShLoc;
	GLint vShLoc;

	GLint lightPosShLoc;
	GLint lightColorShLoc;
	GLint lightPowerShLoc;

	GLint matDiffColorShLoc;
	GLint matSpecColorShLoc;
	GLint matAmbColorShLoc;
	GLint texSamplerShLoc;
	GLint alphaSamplerShLoc;

    glm::vec3 diffColor{ 1.0, 1.0, 1.0 };
    glm::vec3 ambColor{ 0.2, 0.2, 0.2 };
    glm::vec3 specColor{ 0, 0, 0 };
    glm::vec3 lightColor{ 1.0, 1.0, 1.0};
    float lightPower = 5;
};

#endif
