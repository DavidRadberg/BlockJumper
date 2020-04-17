
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
    transpose(pos - bb_.get_mid());
}
