#pragma once

#include "mesh.h"

class Mario : public Mesh {
public:
    Mario(TEXTURES texture);

    void animate(const CharacterState & state) override;
    void animate_walk(float s);

private:
    std::vector<int> left_leg_indices_;
    std::vector<int> right_leg_indices_;
    std::vector<int> left_arm_indices_;
    std::vector<int> right_arm_indices_;

    void set_rotation_right_arm(float angle);
    void set_rotation_left_arm(float angle);
    void set_rotation_right_leg(float angle);
    void set_rotation_left_leg(float angle);

    float walk_state_ = 0.0;
};
