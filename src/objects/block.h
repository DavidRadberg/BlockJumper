
#pragma once

#include "textures.h"
#include "object.h"

#include <glm/glm.hpp>
#include <vector>

class Block : public Object {
public:
    Block(const glm::vec3 & base_point, const glm::vec3 & opposite_point, TEXTURES texture = TEXTURES::STONE, bool norm_texture = true);

private:
    glm::vec3 base_point_;
    glm::vec3 opposite_point_;

    bool norm_texture_;
};