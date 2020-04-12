
#pragma once

#include "textures.h"

#include <vector>
#include <glm/glm.hpp>

class Object {
public:
    const std::vector<float> & get_vertices() { return vertices_; };
    const std::vector<float> & get_uv() { return uv_; };
    const std::vector<int> & get_indices() { return indices_; };
    const char * get_texture_path() { return Textures::get_texture_path(texture_); };

protected:
    std::vector<float> vertices_;
    std::vector<float> uv_;
    std::vector<int> indices_;

    TEXTURES texture_;
};
