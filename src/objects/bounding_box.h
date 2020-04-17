
#pragma once

#include <glm/glm.hpp>

class BoundingBox {
public:
    void add_point(const glm::vec3 & point);
    void transpose(const glm::vec3 & diff);
    void scale(float factor);
    void reset() { initialized_ = false; };

    const glm::vec3 & get_min() { return min_; };
    const glm::vec3 & get_max() { return max_; };
    glm::vec3 get_mid() { return 0.5f * (min_ + max_); };
    glm::vec3 get_base() { return glm::vec3(0.5 * (min_.x + max_.x), min_.y, 0.5 * (min_.z + max_.z)); };
    glm::vec3 get_size() { return max_ - min_; };
private:
    bool initialized_ = false;
    glm::vec3 min_;
    glm::vec3 max_;
};
