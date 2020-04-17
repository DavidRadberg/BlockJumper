
#include "renderer.h"
#include "character.h"
#include "scene.h"
#include "block.h"
#include "mesh.h"

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

    Mesh mario(MESHES::MARIO, TEXTURES::MARIO_MAIN);

    Scene scene(window, mario, (float) width / (float) height, 60.0);

    Block block(glm::vec3(-50.0, 0.0, -50.0), glm::vec3(50.0, -1.0, 50.0), TEXTURES::GRASS, true);
    scene.add_object(block);

    Block block2(glm::vec3(10.0, 10.0, 0.0), glm::vec3(7.0, 3.0, 6.0), TEXTURES::STONE, true);
    scene.add_object(block2);

    Block block3(glm::vec3(-2.0, 0.0, -1.0), glm::vec3(-4.0, 1.0, 1.0), TEXTURES::STONE, true);
    scene.add_object(block3);

    Block block4(glm::vec3(-2.0, 0.0, -10.0), glm::vec3(-3.0, 1.0, -11.0), TEXTURES::STONE, true);
    scene.add_object(block4);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) {
        scene.render_scene();
    }

    glfwTerminate();
    return 0;
}
