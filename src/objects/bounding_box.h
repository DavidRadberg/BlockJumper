
#pragma once

#include <glm/glm.hpp>

class BoundingBox {
public:
    void add_point(const glm::vec3 & point);
    void transpose(const glm::vec3 & diff);
    void scale(float factor);
    void reset() { initialized_ = false; };

    const glm::vec3 & get_min() const { return min_; };
    const glm::vec3 & get_max() const { return max_; };
    glm::vec3 get_mid() const { return 0.5f * (min_ + max_); };
    glm::vec3 get_base() const { return glm::vec3(0.5 * (min_.x + max_.x), min_.y, 0.5 * (min_.z + max_.z)); };
    glm::vec3 get_size() const { return max_ - min_; };
private:
    bool initialized_ = false;
    glm::vec3 min_;
    glm::vec3 max_;
};
