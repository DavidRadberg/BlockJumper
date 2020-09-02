
#include "character.h"
#include "spdlog/spdlog.h"


Character::Character(GLFWwindow * window, Camera & camera, Object & object)
    : window_(window), camera_(camera), object_(object)
{
    position_ = object_.get_mid();
    last_process_ = glfwGetTime();
}


void Character::process_input(const std::vector<Object> & objects)
{
    // run sudo xboxdrv --silent to start xbox control driver
    state_.t = glfwGetTime();
    state_.dt = state_.t - last_process_;
    last_process_ = state_.t;

    glfwGetGamepadState(GLFW_JOYSTICK_1, &gamepad_state_);

    if (gamepad_state_.buttons[GLFW_GAMEPAD_BUTTON_START] || glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        spdlog::info("Closing glfw window");
        glfwSetWindowShouldClose(window_, true);
    }

    update_position(state_.dt, objects);
    update_angles(state_.dt);
    camera_.update_lookat(position_);
    camera_.update_angles(cam_angle_zx_, cam_angle_y_);
    camera_.update_mvp();
    object_.animate(state_);
    object_.set_position(position_);
    object_.set_rotation(direction_);
    update_collisions(objects);
}

void Character::update_position(float dt, const std::vector<Object> & objects)
{
    glm::vec3 movement;

    float input_x = get_axis_input(GLFW_GAMEPAD_AXIS_LEFT_X);
    float input_y = get_axis_input(GLFW_GAMEPAD_AXIS_LEFT_Y);
    update_state(objects);

    // movement is relative to cam angle
    movement.x =  glm::cos(cam_angle_zx_) * input_x + glm::sin(cam_angle_zx_) * input_y;
    movement.z = -glm::sin(cam_angle_zx_) * input_x + glm::cos(cam_angle_zx_) * input_y;

   if (movement.z != 0.0 || movement.x != 0.0) {
       if (movement.x == 0.0) {
           direction_ = movement.z > 0.0 ? 0.0 : M_PI;
       } else if (movement.z == 0.0) {
           direction_ = movement.x > 0.0 ? -0.5 * M_PI : 0.5 * M_PI;
       } else {
           direction_ = glm::atan(-movement.x / movement.z);
           if (movement.z < 0.0) {
               direction_ += M_PI;
           }
       }
   }

    if (debug_mode_) {
        movement.y = (float) gamepad_state_.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER] - (float) gamepad_state_.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER];
    } else if (state_.is_jumping()) {
        movement.y = jump_speed_;
    } else if (state_.is_falling()) {
        movement.y = -fall_speed_;
    }

    position_ += movement * dt * move_speed_;
    state_.speed = glm::sqrt(input_x * input_x + input_y * input_y);
}

bool Character::update_collisions(const std::vector<Object> & objects)
{
    glm::vec3 collision_pos(0.0);
    for (const Object & obj : objects) {
        if (obj.test_collision(object_, collision_pos)) {
            position_ = collision_pos;
            object_.set_position(position_);
            return true;
        }
    }
    return false;
}

void Character::update_angles(float dt)
{
    cam_angle_y_ += get_axis_input(GLFW_GAMEPAD_AXIS_RIGHT_Y) * dt * angle_speed_;
    cam_angle_y_ = glm::clamp(cam_angle_y_, (float) -M_PI * 0.48f, (float) M_PI * 0.48f);
    cam_angle_zx_ += -get_axis_input(GLFW_GAMEPAD_AXIS_RIGHT_X) * dt * angle_speed_;
}

float Character::get_axis_input(int axis)
{
    if (glm::abs(gamepad_state_.axes[axis]) > epsilon_) {
        return -gamepad_state_.axes[axis];
    } else {
        return 0.0;
    }
}

float Character::get_ground_height(const std::vector<Object> & objects)
{
    float ground_height = position_.y - 1000.0;
    for (const Object & obj : objects) {
        if (obj.inside_plane(glm::vec2(position_.x, position_.z))) {
            float height = obj.get_top().y;
            if (height > ground_height && height < object_.get_top().y) {
                ground_height = height;
            }
        }
    }

    return ground_height;
}

void Character::update_state(const std::vector<Object> & objects)
{
    float cur_time = glfwGetTime();
    float dt = cur_time - prev_state_time_;
    float ground_height = get_ground_height(objects);
    if (state_.is_standing()) {
        if (ground_height < object_.get_base().y - 0.02) {
            state_.action = CharacterActions::FALLING;
            prev_state_time_ = cur_time;
        } else if (gamepad_state_.buttons[GLFW_GAMEPAD_BUTTON_A]) {
            state_.action = CharacterActions::JUMPING;
            prev_state_time_ = cur_time;
        }
    } else if (state_.is_jumping() && dt > 0.3) {
        state_.action = CharacterActions::FALLING;
        prev_state_time_ = cur_time;
    } else if (state_.is_falling()) {
        if ((ground_height + 0.02) > object_.get_base().y) {
            state_.action = CharacterActions::STANDING;
            position_.y = position_.y - object_.get_base().y + ground_height;
        }
    }
}
