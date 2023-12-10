#pragma once

#include "GL/glew.h"

class BufferObject {
public:
    BufferObject(GLenum type, GLuint binding, GLuint size);
    virtual ~BufferObject();

private:
    GLuint id;
};