
#include "character.h"
#include "spdlog/spdlog.h"

void Character::process_input() {
    glfwGetGamepadState(GLFW_JOYSTICK_1, &state_);
    
    if (state_.buttons[GLFW_GAMEPAD_BUTTON_A] || glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        spdlog::info("Closing glfw window");
        glfwSetWindowShouldClose(window_, true);
    }

    //spdlog::info("right x is {}", state_.axes[GLFW_GAMEPAD_AXIS_LEFT_X]);
}