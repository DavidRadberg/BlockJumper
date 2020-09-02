
#pragma once

#include "textures.h"
#include "bounding_box.h"
#include "character_state.h"

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
    glm::vec3 get_top() const { return bb_.get_top(); };
    glm::vec3 get_size() const { return bb_.get_size(); };

    bool inside_plane(const glm::vec2 & pos) const;


    void set_position(const glm::vec3 & pos);
    void set_rotation(float xz, float y = 0.0);
    void transpose(const glm::vec3 & diff);
    void scale(float factor);

    bool test_collision(const Object & obj, glm::vec3 & pos) const;

    virtual void animate(const CharacterState & state) {};

    void rotate_points_x(const std::vector<int> points, glm::vec3 axis, float angle);
    void rotate_points_z(const std::vector<int> points, glm::vec3 axis, float angle);

protected:
    std::vector<float> org_vertices_;
    std::vector<float> vertices_;
    std::vector<float> uv_;
    std::vector<int> indices_;

    TEXTURES texture_;
    BoundingBox bb_;
    BoundingBox org_bb_;

    float angle_xz_ = 0.0;
    float angle_y_ = 0.0;

    void update_bb();
    void update_org_bb();
    void rotate(float xz, float y = 0.0);

    void transpose_org(const glm::vec3 & diff);
    void scale_org(float factor);

    void reset_vertices();
    void set_org_vertices();
};
