#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:
    Camera(float aspect, float fov = 60, float z_near = 0.1, float z_far = 100.0);

    void update_size(int width, int height);
    void update_lookat(const glm::vec3 & lookat) { lookat_ = lookat; };
    void update_angles(float angle_zx, float angle_y);
    const glm::mat4 & get_mvp() const { return mvp_; };
    void update_mvp();

private:
    glm::vec3 lookat_ = glm::vec3(0.0, 0.0, 0.0);
    float angle_zx_ = 0.0; // angle in xz plane
    float angle_y_ = 0.2 * M_PI; // angle along y axis
    float radius_ = 5.0;

    glm::mat4 projection_;
    glm::mat4 mvp_;
};
