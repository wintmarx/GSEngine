#ifndef GSENGINE_MODEL
#define GSENGINE_MODEL

#include <string>

#include "Graphics/Shaders/ShaderProgram.h"
#include "LibExports.h"
#include "glm/glm.hpp"

class Model {
public:
    GSENGINE_API explicit Model(const std::string& filePath);
    GSENGINE_API Model() = default;
    GSENGINE_API ~Model();
    GSENGINE_API void Draw(const glm::mat4& model, const glm::mat4& projection,
                           const glm::mat4& view, const glm::vec3& lightPos);
    GSENGINE_API void AddTexture(GLuint textureId);
    int GetVerticesCount() const { return verticesCount; }

private:
    void LoadModel(const std::string& filePath);
    void AddShader(ShaderProgram& program);

    ShaderProgram program;

    GLuint vertexBuffer{};
    GLuint vao{};
    GLuint indexBuffer{};
    GLuint textureId{};
    GLuint alphaId{};
    int verticesCount{};
    int indexCount{};

    GLuint shadingProgramID{};
    GLint mvpShLoc{};
    GLint mShLoc{};
    GLint vShLoc{};

    GLint lightPosShLoc{};
    GLint lightColorShLoc{};
    GLint lightPowerShLoc{};

    GLint matDiffColorShLoc{};
    GLint matSpecColorShLoc{};
    GLint matAmbColorShLoc{};
    GLint texSamplerShLoc{};
    GLint alphaSamplerShLoc{};

    glm::vec3 diffColor{1.0, 1.0, 1.0};
    glm::vec3 ambColor{0.2, 0.2, 0.2};
    glm::vec3 specColor{1, 1, 1};
    glm::vec3 lightColor{1.0, 1.0, 1.0};
    float lightPower = 2;
};

#endif
