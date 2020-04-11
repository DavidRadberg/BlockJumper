
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:
    Camera(int width, int height_, float fov = 60);

    void update_size(int width, int height);
    const glm::mat4 & get_mvp() const { return mvp_; };

private:
    glm::vec3 lookat_ = glm::vec3(0.0, 0.0, 0.0);
    float angle_zx_ = 0.0; // angle in xz plane
    float angle_y_ = 0.2 * M_PI; // angle along y axis
    float radius_ = 3.0;
    int width_, height_;
    float z_near_ = 0.1;
    float z_far_ = 100.0;

    glm::mat4 projection_;
    glm::mat4 mvp_;

    void update_mvp(); 
};