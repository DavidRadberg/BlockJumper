#pragma once

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

    unsigned int vbo_;
    unsigned int vao_;

    unsigned int vertex_shader_;
    unsigned int fragment_shader_;
    unsigned int shader_program_;
};
