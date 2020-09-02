
#include "renderer.h"
#include "character.h"
#include "scene.h"
#include "block.h"
#include "mario.h"
#include "rng_util.h"

#include "spdlog/spdlog.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}



void fill_scene(Scene * scene, int n_blocks = 100, float range = 70.0, float max_height = 8.0, float max_width = 15.0)
{
    std::shared_ptr<Block> ground = std::make_shared<Block>(glm::vec3(-range, -10.0, -range), glm::vec3(range + max_width, 0.0, range + max_width), TEXTURES::GRASS, true);
    scene->add_object(ground);

    srand(1234);

    for (int i = 0; i < n_blocks; i++) {
        float x = generate_random_float(range, -range);
        float z = generate_random_float(range, -range);

        float width = generate_random_float(max_width, 1.0);
        float depth = generate_random_float(max_width, 1.0);
        float height = generate_random_float(max_height, 1.0);

        std::shared_ptr<Block> block = std::make_shared<Block>(glm::vec3(x, 0.0, z), glm::vec3(x + width, height, z + depth), TEXTURES::STONE, true);
        scene->add_object(block);
    }
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

    GLFWwindow* window = glfwCreateWindow(width, height, "BlockJumper", NULL, NULL);
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

    std::shared_ptr<Mario> mario = std::make_shared<Mario>(TEXTURES::MARIO_MAIN);
    Scene scene(window, mario, (float) width / (float) height, 60.0);

    fill_scene(&scene);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) {
        scene.render_scene();
    }

    glfwTerminate();
    return 0;
}
