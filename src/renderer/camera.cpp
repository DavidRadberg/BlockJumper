
#include "camera.h"
#include "spdlog/spdlog.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


Camera::Camera(int width, int height, float fov) 
    : width_(width), height_(height)
{
    projection_ = glm::perspective(glm::radians(fov), (float) width_ / (float) height, z_near_, z_far_);
    update_mvp();
}

void Camera::update_mvp() {
    glm::vec3 direction;
    direction.y = -glm::sin(angle_y_);
    float xz_radius = glm::cos(angle_y_);

    direction.x = xz_radius * glm::sin(angle_zx_);
    direction.z = xz_radius * glm::cos(angle_zx_);

    glm::mat4 view = glm::lookAt(lookat_ - radius_ * direction, lookat_, glm::vec3(0.0, 1.0, 0.0));
    mvp_ = projection_* view;
}

void Camera::update_angles(float angle_zx, float angle_y)
{
    angle_zx_ = angle_zx;
    angle_y_ = angle_y;
}
