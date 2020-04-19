
#include "object.h"

void Object::update_bb() {
    bb_.reset();
    for (int i = 0; i < vertices_.size(); i+=3) {
        bb_.add_point(glm::vec3(vertices_[i], vertices_[i + 1], vertices_[1 + 2]));
    }
}

void Object::transpose(const glm::vec3 & diff) {
    for (int i = 0; i < vertices_.size(); i+=3) {
        vertices_[i] += diff.x;
        vertices_[i + 1] += diff.y;
        vertices_[i + 2] += diff.z;
    }
    bb_.transpose(diff);
}

void Object::scale(float factor) {
    for (float & v : vertices_) {
        v *= factor;
    }
    bb_.scale(factor);
}

void Object::set_position(const glm::vec3 & pos) {
    transpose(pos - get_mid());
}

void Object::set_rotation(float xz, float y)
{
    if (xz != angle_xz_) {
        rotate(xz - angle_xz_);
        angle_xz_ = xz;
    }
}

void Object::rotate(float xz, float y)
{
    float diff_x = 0.0, diff_z = 0.0;
    glm::vec3 mid = get_mid();
    for (int i = 0; i < vertices_.size(); i+=3) {
        diff_x = vertices_[i] - mid.x;
        diff_z = vertices_[i + 2] - mid.z;

        vertices_[i] = mid.x + diff_x * glm::cos(xz) - diff_z * glm::sin(xz);
        vertices_[i + 2] = mid.z + diff_x * glm::sin(xz) + diff_z * glm::cos(xz);
    }
}