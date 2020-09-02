#pragma once

#include "shader.h"
#include "camera.h"
#include "object.h"

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

class Renderer {
public:
    Renderer(const Camera & camera, std::shared_ptr<Object> object);
    void render();

private:
    Shader shader_;
    const Camera & camera_;
    std::shared_ptr<Object> object_;

    unsigned int vbo_pos_;
    unsigned int vbo_uv_;
    unsigned int vao_;
    unsigned int ebo_;
    unsigned int texture_;
};
