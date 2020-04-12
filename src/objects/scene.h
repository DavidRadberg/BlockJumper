
#pragma once

#include "object.h"
#include "global_renderer.h"
#include "character.h"

class Scene {
public:
    Scene(GLFWwindow * window, float aspect = 1.6, float fov = 60.0);

    void add_object(Object & object);
    void render_scene();
private:
    GLFWwindow * window_;

    std::vector<Object> objects_;
    Camera camera_;
    GlobalRenderer renderer_;
    Character character_;
};