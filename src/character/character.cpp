
#include "character.h"
#include "spdlog/spdlog.h"


Character::Character(GLFWwindow * window, Camera & camera) : window_(window), camera_(camera)
{
    position_ = glm::vec3(0.0, 0.0, 0.0);
    last_process_ = glfwGetTime();
}


void Character::process_input()
{
    // run sudo xboxdrv --silent to start xbox control driver
    float dt = glfwGetTime() - last_process_;
    last_process_ = glfwGetTime();

    glfwGetGamepadState(GLFW_JOYSTICK_1, &state_);
    
    if (state_.buttons[GLFW_GAMEPAD_BUTTON_START] || glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        spdlog::info("Closing glfw window");
        glfwSetWindowShouldClose(window_, true);
    }

    update_position(dt);
    update_angles(dt);
    camera_.update_lookat(position_);
    camera_.update_angles(cam_angle_zx_, cam_angle_y_);
    camera_.update_mvp();
}

void Character::update_position(float dt)
{
    glm::vec3 movement;

    float input_x = get_axis_input(GLFW_GAMEPAD_AXIS_LEFT_X);
    float input_y = get_axis_input(GLFW_GAMEPAD_AXIS_LEFT_Y);

    // movement is relative to cam angle
    movement.x =  glm::cos(cam_angle_zx_) * input_x + glm::sin(cam_angle_zx_) * input_y;
    movement.z = -glm::sin(cam_angle_zx_) * input_x + glm::cos(cam_angle_zx_) * input_y;

    movement.y = (float) state_.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER] - (float) state_.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER];
    position_ += movement * dt * move_speed_;
}

void Character::update_angles(float dt)
{
    cam_angle_y_ += get_axis_input(GLFW_GAMEPAD_AXIS_RIGHT_Y) * dt * angle_speed_;
    cam_angle_zx_ += -get_axis_input(GLFW_GAMEPAD_AXIS_RIGHT_X) * dt * angle_speed_;
}

float Character::get_axis_input(int axis)
{
    if (glm::abs(state_.axes[axis]) > epsilon_) {
        return -state_.axes[axis];
    } else {
        return 0.0;
    }
}