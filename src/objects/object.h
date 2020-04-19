
#pragma once

#include "textures.h"
#include "bounding_box.h"

#include <vector>
#include <glm/glm.hpp>

class Object {
public:
    const std::vector<float> & get_vertices() { return vertices_; };
    const std::vector<float> & get_uv() { return uv_; };
    const std::vector<int> & get_indices() { return indices_; };
    const char * get_texture_path() { return Textures::get_texture_path(texture_); };

    const BoundingBox & get_bb() { return bb_; };

    glm::vec3 get_mid() const { return bb_.get_mid(); };
    glm::vec3 get_base() const { return bb_.get_base(); };
    glm::vec3 get_size() const { return bb_.get_size(); };


    void set_position(const glm::vec3 & pos);
    void set_rotation(float xz, float y = 0.0);
    void transpose(const glm::vec3 & diff);
    void scale(float factor);

protected:
    std::vector<float> vertices_;
    std::vector<float> uv_;
    std::vector<int> indices_;

    TEXTURES texture_;
    BoundingBox bb_;

    float angle_xz_ = 0.0;
    float angle_y_ = 0.0;

    void update_bb();
    void rotate(float xz, float y = 0.0);
};
