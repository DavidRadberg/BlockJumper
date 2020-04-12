#pragma once

#include "shader.h"
#include "camera.h"
#include "object.h"

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
public:
    Renderer(const Camera & camera, Object & object);
    void render();

private:
    Shader shader_;
    const Camera & camera_;
    Object & object_;

    unsigned int vbo_pos_;
    unsigned int vbo_uv_;
    unsigned int vao_;
    unsigned int ebo_;
    unsigned int texture_;
};
