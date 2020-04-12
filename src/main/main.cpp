
#include "renderer.h"
#include "character.h"
#include "object.h"
#include "block.h"

#include "spdlog/spdlog.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    int width = 1200;
    int height = 900;

    spdlog::info("Initializing GLFW...");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        spdlog::critical("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::critical("Failed to initialize GLAD");
        return -1;
    }

    glViewport(0, 0, width, height);

    Camera camera(width, height);
    Character character(window, camera);
    Block block(glm::vec3(-50.0, 0.0, -50.0), glm::vec3(50.0, -1.0, 50.0), TEXTURES::GRASS, true);
    Block block2(glm::vec3(0.0, 0.0, 0.0), glm::vec3(7.0, 3.0, 6.0), TEXTURES::STONE, true);
    Renderer renderer(camera, block);
    Renderer renderer2(camera, block2);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        character.process_input();
        renderer.render();
        renderer2.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
