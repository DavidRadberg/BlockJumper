#pragma once

#include "shader.h"

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
public:
    Renderer();
    void render();
private:
    std::vector<float> vertices_;
    std::vector<float> uv_;
    std::vector<int> indices_;

    Shader shader_;

    unsigned int vbo_pos_;
    unsigned int vbo_uv_;
    unsigned int vao_;
    unsigned int ebo_;
    unsigned int texture_;
};
