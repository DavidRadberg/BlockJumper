
#include "bounding_box.h"
#include "spdlog/spdlog.h"

void BoundingBox::add_point(const glm::vec3 & point)
{
    if (!initialized_) {
        min_ = point;
        max_ = point;
        initialized_ = true;
    } else {
        if (point.x < min_.x) min_.x = point.x;
        if (point.y < min_.y) min_.y = point.y;
        if (point.z < min_.z) min_.z = point.z;
        if (point.x > max_.x) max_.x = point.x;
        if (point.y > max_.y) max_.y = point.y;
        if (point.z > max_.z) max_.z = point.z;
    }
}

void BoundingBox::transpose(const glm::vec3 & diff) {
    min_ += diff;
    max_ += diff;
}

void BoundingBox::scale(float factor) {
    min_ *= factor;
    max_ *= factor;
}

void BoundingBox::dbg_print() const
{
    spdlog::info("bb min is {}, {}, {}", min_.x, min_.y, min_.z);
    spdlog::info("bb max is {}, {}, {}", max_.x, max_.y, max_.z);
}