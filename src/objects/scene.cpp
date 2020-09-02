
#include "scene.h"
#include "spdlog/spdlog.h"

Scene::Scene(GLFWwindow * window, std::shared_ptr<Object> main_object, float aspect, float fov)
    : window_(window), camera_(aspect, fov), renderer_(window_, camera_), character_(window_, camera_, main_object)
{
    add_object(main_object, true);
}

void Scene::add_object(std::shared_ptr<Object> object, bool main)
{
    spdlog::info("adding object to scene");
    if (!main) {
        objects_.push_back(object);
    }
    renderer_.add_renderer(object);
}

void Scene::render_scene()
{
    character_.process_input(objects_);
    renderer_.render();
    glfwPollEvents();
}