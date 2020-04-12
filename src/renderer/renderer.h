#pragma once

#include "shader.h"
#include "camera.h"
#include "block.h"

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
public:
    Renderer(Camera & camera, Block & block);
    void render();

private:
    Shader shader_;
    Camera & camera_;
    Block block_;

    unsigned int vbo_pos_;
    unsigned int vbo_uv_;
    unsigned int vao_;
    unsigned int ebo_;
    unsigned int texture_;
};
