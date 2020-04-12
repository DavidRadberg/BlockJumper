
#include "block.h"

Block::Block(const glm::vec3 & base_point, const glm::vec3 & opposite_point, TEXTURES texture, bool norm_texture)
    : base_point_(base_point), opposite_point_(opposite_point), texture_(texture), norm_texture_(norm_texture)
{
    float tmp_vertices[] = {
        0.0,  0.0, 0.0,
        1.0,  0.0, 0.0,
        1.0,  1.0, 0.0,
        0.0,  1.0, 0.0,

        0.0,  0.0, 1.0,
        1.0,  0.0, 1.0,
        1.0,  1.0, 1.0,
        0.0,  1.0, 1.0,

        0.0,  0.0, 1.0,
        1.0,  0.0, 1.0,
        1.0,  1.0, 1.0,
        0.0,  1.0, 1.0
    };

    for (float v : tmp_vertices) {
        vertices_.push_back(v);
    }

    float tmp_uv[] = {
        0.0,  0.0,
        1.0,  0.0,
        1.0,  1.0,
        0.0,  1.0,

        1.0,  0.0,
        2.0,  0.0,
        2.0,  1.0,
        1.0,  1.0,

        0.0, -1.0,
        1.0, -1.0,
        1.0,  2.0,
        0.0,  2.0
    };

    for (float uv : tmp_uv) {
        uv_.push_back(uv);
    }

    unsigned int tmp_indices[] = {
        // sides
        0, 1, 2,
        2, 3, 0,

        1, 5, 6,
        6, 2, 1,

        5, 4, 7,
        7, 6, 5,

        4, 0, 3,
        3, 7, 4,

        // top and bottom
        8, 9, 1,
        1, 0, 8,

        3, 2, 10,
        10, 11, 3
    };

    for (int i : tmp_indices) {
        indices_.push_back(i);
    }
}

const char * Block::get_texture_path()
{
    return Textures::get_texture_path(texture_);
}