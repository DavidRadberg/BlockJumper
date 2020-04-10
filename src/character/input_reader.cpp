
#include "input_reader.h"
#include "spdlog/spdlog.h"

void InputReader::process_input() {
    glfwGetGamepadState(GLFW_JOYSTICK_1, &state_);
    
    if (state_.buttons[GLFW_GAMEPAD_BUTTON_A] || glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        spdlog::info("Closing glfw window");
        glfwSetWindowShouldClose(window_, true);
    }
}