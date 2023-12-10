#ifndef GSENGINE_GRAPHICS_HEADER
#define GSENGINE_GRAPHICS_HEADER

#include "Graphics/Shapes/Circle.h"
#include "Graphics/Shapes/Line.h"
#include "LibExports.h"

class TexturesController;

class Graphics {
public:
    GSENGINE_API Graphics();
    GSENGINE_API ~Graphics();
    GSENGINE_API void DrawLine(const glm::vec3& b, const glm::vec3& e, float width,
                               const glm::vec4& color, const glm::mat4& projection,
                               const glm::mat4& view) const;
    GSENGINE_API void DrawCircle(const glm::vec3& c, float radius, float width,
                                 const glm::vec4& color, const glm::mat4& projection,
                                 const glm::mat4& view) const;

private:
    static void InitGLEW();

private:
    bool isInit = false;
    mutable Line line;
    mutable Circle circle;
    std::unique_ptr<TexturesController> texturesCtrl;
};

#endif