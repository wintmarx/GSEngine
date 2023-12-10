#define GSENGINE_EXPORT

#include "Graphics/Shapes/Sprites/CommonSprite.h"

#include <iostream>

#include "Graphics/Shaders/SpriteShaderProgram.h"

CommonSprite::CommonSprite(const glm::vec3& p) : Sprite(p) {}

std::vector<SpriteShaderProgram*> CommonSprite::shaderPrograms;
void CommonSprite::SetShader(const char* vFilePath, const char* fFilePath) {
    /*bool isMatch = false;
    for (unsigned int i = 0; i < shaderPrograms.size(); i++)
    {
            if (shaderPrograms[i]->IsShaderEqual(vFilePath, fFilePath))
            {
                    isMatch = true;
                    currentShaderProgram = i;
            }
    }
    if (!isMatch)
    {*/
    shaderPrograms.push_back(new SpriteShaderProgram(vFilePath, fFilePath));
    currentShaderProgram = shaderPrograms.size() - 1;
    //}
}

void CommonSprite::Draw(const glm::mat4& projection, const glm::mat4& view) {
    if (shaderPrograms.empty()) {
        std::cout << "\nThere are no any shaders attached to sprite";
        return;
    }

    if (currentShaderProgram == -1) {
        std::cout << "\nShader is not set";
        return;
    }

    // std::cout << std::endl << "ShaderInfo: " << currentShaderProgram;
    shaderPrograms[currentShaderProgram]->Enable();
    // std::cout << std::endl << shaderPrograms[currentShaderProgram]->id;

    if (textureId > 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glUniform1i(shaderPrograms[currentShaderProgram]->texSamplerShLoc, 0);
        // std::cout << std::endl << shaderPrograms[currentShaderProgram]->texSamplerShLoc;
    }

    glUniformMatrix4fv(shaderPrograms[currentShaderProgram]->mvpShLoc, 1, GL_FALSE,
                       &(projection * view * model)[0][0]);

    glUniformMatrix3fv(shaderPrograms[currentShaderProgram]->texRegionShLoc, 1, GL_FALSE,
                       &(textureRegion)[0][0]);
    // std::cout << std::endl << shaderPrograms[currentShaderProgram]->mvpShLoc;

    glUniform4fv(shaderPrograms[currentShaderProgram]->matDiffColorShLoc, 1, &(color)[0]);
    // std::cout << std::endl << shaderPrograms[currentShaderProgram]->matDiffColorShLoc;

    if (textureId > 0 && color.x >= 0) {
        glUniform1i(shaderPrograms[currentShaderProgram]->isColoredShLoc, 1);
    } else {
        glUniform1i(shaderPrograms[currentShaderProgram]->isColoredShLoc, 0);
    }
    // std::cout << std::endl << shaderPrograms[currentShaderProgram]->isColoredShLoc;

    glBindVertexArray(vertexArrayObject);

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
    // glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);

    shaderPrograms[currentShaderProgram]->Disable();
}

void CommonSprite::PrintInfo() {
    std::cout << width << "; " << height << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << model[i][j] << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
