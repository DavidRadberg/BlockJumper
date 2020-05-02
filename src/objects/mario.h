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

    float walk_state_ = 0.0;
};
