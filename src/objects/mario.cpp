#include "mario.h"

#include "spdlog/spdlog.h"

Mario::Mario(TEXTURES texture) : Mesh(MESHES::MARIO, texture) {
    for (int i = 0; i < vertices_.size() / 3; i++) {
        if (vertices_[3 * i + 1] < 0.5 && vertices_[3 * i] > 0.0) {
            left_leg_indices_.push_back(i);
        } else if (vertices_[3 * i + 1] < 0.5 && vertices_[3 * i] < 0.0) {
            right_leg_indices_.push_back(i);
        }
    }
}

void Mario::animate(const CharacterState & state) {
    reset_vertices();

    if (state.is_running()) {
        walk_state_ += state.speed * state.dt;
        animate_walk(walk_state_);
    }

}

void Mario::animate_walk(float s) {
    float left_leg_rot = -0.2 + 0.8 * glm::cos(25.0 * s);
    float right_leg_rot = -0.2 + -0.8 * glm::cos(25.0 * s);

    rotate_points_x(left_leg_indices_, glm::vec3(0.0, 0.7, 0.0), left_leg_rot);
    rotate_points_x(right_leg_indices_, glm::vec3(0.0, 0.7, 0.0), right_leg_rot);
}