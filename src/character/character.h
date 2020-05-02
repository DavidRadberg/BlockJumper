
#pragma once

#include "camera.h"
#include "object.h"
#include "character_state.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


class Character {
public:
    Character(GLFWwindow * window, Camera & camera, Object & object);

    void process_input(const std::vector<Object> & objects_);
    const glm::vec3 & get_position() const { return position_; };

private:
    GLFWwindow * window_;
    Camera & camera_;
    Object & object_;
    GLFWgamepadstate gamepad_state_;

    float last_process_;
    glm::vec3 position_;
    float direction_ = 0.0;
    float cam_angle_y_ = 0.1;
    float cam_angle_zx_ = 0.0;

    void update_position(float dt, const std::vector<Object> & objects);
    void update_angles(float dt);
    float get_axis_input(int axis);

    float move_speed_ = 8.0;
    float jump_speed_ = 4.0;
    float angle_speed_ = 2.0;
    float epsilon_ = 0.2;

    float get_ground_height(const std::vector<Object> & objects);
    void update_state(const std::vector<Object> & objects);

    float prev_state_time_;
    CharacterState state_;

    bool debug_mode_ = false;
};