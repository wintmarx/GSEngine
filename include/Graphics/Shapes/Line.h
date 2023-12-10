#ifndef GRAPHICS_LINE_HEADER
#define GRAPHICS_LINE_HEADER

#include <memory>

#include "GL/glew.h"
#include "LibExports.h"
#include "glm/glm.hpp"

class SpriteShaderProgram;

class Line {
public:
    GSENGINE_API Line();
    GSENGINE_API Line(const glm::vec3& b, const glm::vec3& e, float width, const glm::vec4& color);
    GSENGINE_API ~Line();
    GSENGINE_API void Draw(const glm::mat4& projection, const glm::mat4& view);
    GSENGINE_API void SetLine(const glm::vec3& b, const glm::vec3& e, float width,
                              const glm::vec4& color);

private:
    float width{1.f};
    static constexpr int vertexCount{2};
    static constexpr int dim{3};
    glm::vec4 color{0};
    GLuint vertexBuffer{0};
    GLuint vertexArrayObject{0};
    std::unique_ptr<SpriteShaderProgram> shaderProgram;
};

#endif
