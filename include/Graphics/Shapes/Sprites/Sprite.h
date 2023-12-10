#ifndef GSENGINE_SPRITE_HEADER
#define GSENGINE_SPRITE_HEADER

#include "GL/glew.h"
#include "Graphics/Textures/TexturesController.h"
#include "LibExports.h"
#include "glm/glm.hpp"

class Sprite {
public:
    GSENGINE_API explicit Sprite(const glm::vec3& c);
    GSENGINE_API virtual ~Sprite();
    GSENGINE_API virtual void Draw(const glm::mat4& projection, const glm::mat4& view) = 0;
    GSENGINE_API void SetSize(float width, float height);
    GSENGINE_API void SetTextureShape(float uvX, float uvY, float width, float height);
    GSENGINE_API void SetColor(const glm::vec4& color);
    GSENGINE_API void SetTexture(const char* filePath, bool isStdFolder = true);
    GSENGINE_API void Scale(const glm::vec3& delta);
    GSENGINE_API void Rotate(const glm::vec3& axis, float angle);
    GSENGINE_API void SetAngle(const glm::vec3& axis, float angle);
    GSENGINE_API void SetScale(const glm::vec3& scale);
    GSENGINE_API void SetPosition(float x, float y, float z);
    GSENGINE_API void SetPosition(const glm::vec3& p);
    GSENGINE_API void Translate(float dx, float dy, float dz);
    GSENGINE_API void Translate(const glm::vec3& dPos);
    GSENGINE_API virtual void SetShader(const char* vFilePath, const char* fFilePath) = 0;
    GSENGINE_API void SetActiveShaderProgram(int localShaderProgramId);
    static void SetTexturesController(TexturesController* texturesController);

protected:
    void InitializeSprite();

private:
    void InvalidateModelMatrix();

public:
    float width = 1.f;
    float height = 1.f;

protected:
    glm::mat4 model{1.f};
    glm::mat4 rM{1.f};
    glm::mat4 sM{1.f};
    glm::mat4 tM{1.f};
    glm::mat3 textureRegion{1.f};
    static const int8_t vertexCount = 4;
    static const int8_t indexCount = 6;
    static const int8_t dim = 3;
    glm::vec4 color{1.f};
    static TexturesController* texturesController;
    GLuint textureId = 0;
    int currentShaderProgram = -1;
    GLuint vertexBuffer = 0;
    GLuint indexBuffer = 0;
    GLuint vertexArrayObject = 0;
};

#endif
