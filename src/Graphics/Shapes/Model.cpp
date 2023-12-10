#define GSENGINE_EXPORT

#include "Graphics/Shapes/Model.h"

#include <fstream>
#include <iostream>
#include <vector>

Model::Model(const std::string& filePath) {
    LoadModel(filePath);
    program.AddShader(GL_VERTEX_SHADER, "Model.vs");
    program.AddShader(GL_FRAGMENT_SHADER, "Model.fs");
    program.Link();
    AddShader(program);
}

Model::~Model() {
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vao);
    // glDeleteBuffers(1, &indexBuffer);
}

void Model::LoadModel(const std::string& filePath) {
    std::fstream fileStream;
    std::string line;
    line.reserve(128);
    std::vector<glm::vec3> v;
    std::vector<glm::vec2> vt;
    std::vector<glm::vec3> vn;
    std::vector<float> buf;

    fileStream.open(filePath, std::ios::in);
    if (!fileStream.is_open()) {
        printf("Can not open %s.\n", filePath.c_str());
        return;
    }

    while (std::getline(fileStream, line)) {
        char* p;
        switch (line[0]) {
            case 'v':
                switch (line[1]) {
                    case 't':
                        vt.emplace_back();
                        vt.back().x = std::strtof(line.data() + 2, &p);
                        vt.back().y = std::strtof(p + 1, &p);
                        break;
                    case 'n':
                        vn.emplace_back();
                        vn.back().x = std::strtof(line.data() + 2, &p);
                        vn.back().y = std::strtof(p + 1, &p);
                        vn.back().z = std::strtof(p + 1, &p);
                        break;
                    case ' ':
                    default:
                        v.emplace_back();
                        v.back().x = std::strtof(line.data() + 2, &p);
                        v.back().y = std::strtof(p + 1, &p);
                        v.back().z = std::strtof(p + 1, &p);
                        break;
                }
                break;
            case 'f':
                p = line.data() + 1;
                size_t idx;
                while (p < line.data() + line.size()) {
                    idx = std::strtol(p + 1, &p, 0);
                    if (idx == 0) {
                        printf("Error! Model file [%s] corrupted!", filePath.data());
                        continue;
                    }
                    buf.push_back(v[idx - 1].x);
                    buf.push_back(v[idx - 1].y);
                    buf.push_back(v[idx - 1].z);

                    idx = std::strtol(p + 1, &p, 0);
                    if (idx == 0) {
                        printf("Error! Model file [%s] corrupted!", filePath.data());
                        continue;
                    }
                    buf.push_back(vt[idx - 1].x);
                    buf.push_back(vt[idx - 1].y);

                    idx = std::strtol(p + 1, &p, 0);
                    if (idx == 0) {
                        printf("Error! Model file [%s] corrupted!", filePath.data());
                        continue;
                    }
                    buf.push_back(vn[idx - 1].x);
                    buf.push_back(vn[idx - 1].y);
                    buf.push_back(vn[idx - 1].z);
                }
                break;
        }
    }
    fileStream.close();

    verticesCount = buf.size() / 8;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buf.size(), buf.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 5));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices,
    GL_STATIC_DRAW); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/

    textureId = -1;
    alphaId = -1;
}

void Model::AddShader(ShaderProgram& program) {
    mvpShLoc = program.GetUniformLocation("MVP");
    mShLoc = program.GetUniformLocation("M");
    vShLoc = program.GetUniformLocation("V");

    lightPosShLoc = program.GetUniformLocation("lightPositionW");
    lightColorShLoc = program.GetUniformLocation("lightColor");
    lightPowerShLoc = program.GetUniformLocation("lightPower");

    matSpecColorShLoc = program.GetUniformLocation("materialSpecularColor");
    matDiffColorShLoc = program.GetUniformLocation("materialDiffuseColor");
    matAmbColorShLoc = program.GetUniformLocation("materialAmbientColor");

    texSamplerShLoc = program.GetUniformLocation("textureSampler");
    alphaSamplerShLoc = program.GetUniformLocation("alphaSampler");
}

void Model::Draw(const glm::mat4& model, const glm::mat4& projection, const glm::mat4& view,
                 const glm::vec3& lightPos) {
    program.Enable();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    /*glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, alphaId);*/

    glUniformMatrix4fv(mvpShLoc, 1, GL_FALSE, &(projection * view * model)[0][0]);
    glUniformMatrix4fv(vShLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(mShLoc, 1, GL_FALSE, &model[0][0]);

    glUniform3fv(matDiffColorShLoc, 1, &diffColor[0]);
    glUniform3fv(matSpecColorShLoc, 1, &specColor[0]);
    glUniform3fv(matAmbColorShLoc, 1, &ambColor[0]);

    glUniform3fv(lightPosShLoc, 1, &lightPos[0]);
    glUniform3fv(lightColorShLoc, 1, &lightColor[0]);
    glUniform1f(lightPowerShLoc, lightPower);

    glUniform1i(texSamplerShLoc, 0);
    glUniform1i(alphaSamplerShLoc, 1);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    glBindVertexArray(0);
    glDisable(GL_CULL_FACE);
    program.Disable();
}

void Model::AddTexture(GLuint textureId) {
    if (this->textureId != 0) {
        this->alphaId = textureId;
    } else {
        this->textureId = textureId;
    }
}