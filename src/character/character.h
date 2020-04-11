#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Character {
public:
    Character(GLFWwindow * window) : window_(window) {};

    void process_input();

private:
    GLFWwindow * window_;
    GLFWgamepadstate state_;
};