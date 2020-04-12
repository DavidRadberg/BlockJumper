
#include "scene.h"
#include "spdlog/spdlog.h"

Scene::Scene(GLFWwindow * window, float aspect, float fov)
    : window_(window), camera_(aspect, fov), renderer_(window_, camera_), character_(window_, camera_)
{

}

void Scene::add_object(Object & object)
{
    spdlog::info("adding object to scene");
    objects_.push_back(object);
    renderer_.add_renderer(object);
}

void Scene::render_scene()
{
    character_.process_input();
    renderer_.render();
    glfwPollEvents();
}