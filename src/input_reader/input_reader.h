#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class InputReader {
public:
    InputReader(GLFWwindow * window) : window_(window) {};

    void process_input();

private:
    GLFWwindow * window_;
};