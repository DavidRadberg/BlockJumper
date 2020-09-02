
#include "global_renderer.h"


GlobalRenderer::GlobalRenderer(GLFWwindow * window, const Camera & camera)
    : window_(window), camera_(camera)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void GlobalRenderer::add_renderer(std::shared_ptr<Object> object)
{
    renderers_.push_back(Renderer(camera_, object));
}

void GlobalRenderer::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (Renderer & renderer : renderers_) {
        renderer.render();
    }
    glfwSwapBuffers(window_);
}