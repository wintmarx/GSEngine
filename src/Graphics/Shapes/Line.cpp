#define GSENGINE_EXPORT

#include "Graphics/Shapes/Line.h"

#include "Graphics/Shaders/SpriteShaderProgram.h"

Line::Line()
    : shaderProgram{std::make_unique<SpriteShaderProgram>("CommonSprite.vs", "CommonSprite.fs")}

{
    glGenBuffers(1, &vertexBuffer);
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    float init[] = {0, 0, 0, 0, 0, 0};
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * dim, init, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, dim, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Line::Line(const glm::vec3& b, const glm::vec3& e, float width, const glm::vec4& color) : Line() {
    SetLine(b, e, width, color);
}

Line::~Line() {
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArrayObject);
}

void Line::Draw(const glm::mat4& projection, const glm::mat4& view) {
    shaderProgram->Enable();
    glUniformMatrix4fv(shaderProgram->mvpShLoc, 1, GL_FALSE, &(projection * view)[0][0]);
    glUniform4fv(shaderProgram->matDiffColorShLoc, 1, &color[0]);
    glUniform1i(shaderProgram->isColoredShLoc, 0);
    glBindVertexArray(vertexArrayObject);
    glEnableVertexAttribArray(0);
    glLineWidth(width);
    glDrawArrays(GL_LINES, 0, vertexCount * dim);
    glLineWidth(1.);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shaderProgram->Disable();
}

void Line::SetLine(const glm::vec3& b, const glm::vec3& e, float width, const glm::vec4& color) {
    this->color = color;
    this->width = width;

    float vertices[] = {b.x, b.y, b.z, e.x, e.y, e.z};

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertexCount * dim, vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
