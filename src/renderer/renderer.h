#pragma once

#include "shader.h"

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
public:
    Renderer();

    void render();
    bool check_shader(unsigned int shader);
    bool check_program();

private:
    std::vector<float> vertices_;
    std::vector<int> indices_;

    Shader shader_;

    unsigned int vbo_;
    unsigned int vao_;
    unsigned int ebo_;
};
