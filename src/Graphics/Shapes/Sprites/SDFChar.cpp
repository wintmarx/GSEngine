#define GSENGINE_EXPORT

#include "Graphics/Shapes/Sprites/SDFChar.h"

#include <iostream>

#include "Graphics/Shaders/SdfTextShaderProgram.h"

SDFChar::SDFChar(const glm::vec2& drawParams) : Sprite(glm::vec3(0)) {
    currentShaderProgram = -1;
    params = glm::vec4(drawParams, 0, 0);
    borderColor = glm::vec4(0);
}

std::vector<SdfTextShaderProgram*> SDFChar::shaderPrograms;
void SDFChar::SetShader(const char* vFilePath, const char* fFilePath) {
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
    shaderPrograms.push_back(new SdfTextShaderProgram(vFilePath, fFilePath));
    currentShaderProgram = shaderPrograms.size() - 1;
    //}
}

void SDFChar::Draw(const glm::mat4& projection, const glm::mat4& view) {
    if (shaderPrograms.empty()) {
        std::cout << "There are no any shaders attached to sprite";
        return;
    }

    if (currentShaderProgram == -1) {
        std::cout << "Shader is not set";
        return;
    }

    shaderPrograms[currentShaderProgram]->Enable();

    if (textureId > 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glUniform1i(shaderPrograms[currentShaderProgram]->texSamplerShLoc, 0);
    }

    // std::cout << "Char mat " << glm::to_string(model) << std::endl;
    // std::cout << "------------------------------------" << std::endl;

    glUniformMatrix4fv(shaderPrograms[currentShaderProgram]->mvpShLoc, 1, GL_FALSE,
                       &(projection * view * model)[0][0]);
    glUniformMatrix3fv(shaderPrograms[currentShaderProgram]->texRegionShLoc, 1, GL_FALSE,
                       &(textureRegion)[0][0]);

    glUniform4fv(shaderPrograms[currentShaderProgram]->colorShLoc, 1, &(color)[0]);
    glUniform4fv(shaderPrograms[currentShaderProgram]->borderColorShLoc, 1, &(borderColor)[0]);
    glUniform4fv(shaderPrograms[currentShaderProgram]->paramsShLoc, 1, &(params)[0]);

    glBindVertexArray(vertexArrayObject);

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
    // glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    shaderPrograms[currentShaderProgram]->Disable();
}

void SDFChar::SetBorder(const glm::vec4& borderColor, const glm::vec2& borderDrawParams) {
    this->borderColor = borderColor;
    params.z = borderDrawParams.x;
    params.w = borderDrawParams.y;
}

void SDFChar::DeleteBorder() {
    params.z = 0;
    params.w = 0;
    borderColor.a = 0;
}

void SDFChar::SetBorderParams(const glm::vec2& params) {
    this->params.z = params.x;
    this->params.w = params.y;
}

void SDFChar::SetCharParams(const glm::vec2& params) {
    this->params.x = params.x;
    this->params.y = params.y;
}

void SDFChar::SetParams(const glm::vec4& params) { this->params = params; }

void SDFChar::AddParams(const glm::vec4& delta) {
    this->params += delta;
    printf("\n%f\t| %f\t| %f\t| %f", params.x, params.y, params.z, params.w);
}
