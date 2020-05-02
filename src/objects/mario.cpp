#include "mario.h"

#include "spdlog/spdlog.h"

Mario::Mario(TEXTURES texture) : Mesh(MESHES::MARIO, texture) {
    for (int i = 0; i < vertices_.size() / 3; i++) {
        float x = vertices_[3 * i];
        float y = vertices_[3 * i + 1];
        if (x < 0.0) {
            if (y < 0.5) {
                left_leg_indices_.push_back(i);
            } else if (x < -0.35 && y < 1.3) {
                left_arm_indices_.push_back(i);
            }
        } else {
            if (y < 0.5) {
                right_leg_indices_.push_back(i);
            } else if (x > 0.35 && y < 1.3) {
                right_arm_indices_.push_back(i);
            }
        }
    }

    // set this rotation to org vert so we only have to do this once
    rotate_points_z(left_arm_indices_, glm::vec3(-0.33, 1.05, 0.0),  1.35);
    rotate_points_z(right_arm_indices_, glm::vec3(0.33, 1.05, 0.0), -1.35);
    set_org_vertices();
}

void Mario::animate(const CharacterState & state) {
    reset_vertices();

    if (state.is_running()) {
        walk_state_ += state.speed * state.dt;
        animate_walk(walk_state_);
    } else {
        walk_state_ = 0.0;
    }
}

void Mario::animate_walk(float s) {
    float left_leg_rot =  -0.2 +  0.8 * glm::sin(25.0 * s);
    float right_leg_rot = -0.2 + -0.8 * glm::sin(25.0 * s);

    float left_arm_rot =  -0.3 + -0.9 * glm::sin(25.0 * s + 0.5);
    float right_arm_rot = -0.3 +  0.9 * glm::sin(25.0 * s + 0.5);

    rotate_points_x(left_leg_indices_, glm::vec3(0.0, 0.7, 0.0), left_leg_rot);
    rotate_points_x(right_leg_indices_, glm::vec3(0.0, 0.7, 0.0), right_leg_rot);

    rotate_points_x(left_arm_indices_, glm::vec3(-0.33, 1.05, 0.0), left_arm_rot);
    rotate_points_x(right_arm_indices_, glm::vec3(0.33, 1.05, 0.0), right_arm_rot);

    rotate(0.02 * left_leg_rot);
}