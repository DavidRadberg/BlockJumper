
#include "block.h"
#include "spdlog/spdlog.h"

Block::Block(const glm::vec3 & base_point, const glm::vec3 & opposite_point, TEXTURES texture, bool norm_texture)
    : Object(), base_point_(base_point), opposite_point_(opposite_point), norm_texture_(norm_texture)
{
    glm::vec3 diff = glm::abs(base_point_ - opposite_point_);
    if (diff.x == 0.0 || diff.y == 0.0|| diff.z == 0.0) {
        spdlog::critical("Error block has zero volume!");
        assert(0);
    }

    float tmp_vertices[] = {
        base_point_.x,     base_point_.y,     base_point_.z,
        opposite_point_.x, base_point_.y,     base_point_.z,
        opposite_point_.x, opposite_point_.y, base_point_.z,
        base_point_.x,     opposite_point_.y, base_point_.z,

        base_point_.x,     base_point_.y,     opposite_point_.z,
        opposite_point_.x, base_point_.y,     opposite_point_.z,
        opposite_point_.x, opposite_point_.y, opposite_point_.z,
        base_point_.x,     opposite_point_.y, opposite_point_.z,

        base_point_.x,     base_point_.y,     opposite_point_.z,
        opposite_point_.x, base_point_.y,     opposite_point_.z,
        opposite_point_.x, opposite_point_.y, opposite_point_.z,
        base_point_.x,     opposite_point_.y, opposite_point_.z,

        base_point_.x,     base_point_.y,     base_point_.z,
        opposite_point_.x, opposite_point_.y, base_point_.z,
    };

    for (float v : tmp_vertices) {
        vertices_.push_back(v);
    }

    float uv_x = 1.0, uv_y = 1.0, uv_z = 1.0;
    if (norm_texture_) {
        uv_x = diff.x;
        uv_y = diff.y;
        uv_z = diff.z;
    }

    float tmp_uv[] = {
        0.0,  0.0,
        uv_x, 0.0,
        uv_x, uv_y,
        0.0,  uv_y,

        2 * uv_x + uv_z, 0.0,
        uv_x + uv_z,     0.0,
        uv_x + uv_z,     uv_y,
        2 * uv_x + uv_z, uv_y,

        0.0, -uv_z,
        uv_x, -uv_z,
        uv_x,  uv_y + uv_z,
        0.0,  uv_y + uv_z,

        2 * uv_x + 2 * uv_z, 0.0,
        2 * uv_x + 2 * uv_z, uv_y
    };

    for (float f : tmp_uv) {
        uv_.push_back(f);
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

    texture_ = texture;
    update_bb();
}
