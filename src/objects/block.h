
#pragma once

#include "textures.h"

#include <glm/glm.hpp>
#include <vector>

class Block {
public:
    Block(const glm::vec3 & base_point, const glm::vec3 & opposite_point, TEXTURES texture = TEXTURES::BRICK_TEXTURE, bool norm_texture = true);

    const std::vector<float> & get_vertices() { return vertices_; };
    const std::vector<float> & get_uv() { return uv_; };
    const std::vector<int> & get_indices() { return indices_; };
    const char * get_texture_path();

private:
    glm::vec3 base_point_;
    glm::vec3 opposite_point_;

    std::vector<float> vertices_;
    std::vector<float> uv_;
    std::vector<int> indices_;

    TEXTURES texture_;
    bool norm_texture_;
};