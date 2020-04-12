
#pragma once

#include "renderer.h"
#include "camera.h"

class GlobalRenderer {
public:
    GlobalRenderer(GLFWwindow * window, const Camera & camera);

    void add_renderer(Object & object);
    void render();

private:
    GLFWwindow * window_;
    const Camera & camera_;
    std::vector<Renderer> renderers_;

};