#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    bool compile_shader(const char* vertexPath, const char* fragmentPath);
    void run();

    void set_bool(const std::string &name, bool value);
    void set_int(const std::string &name, int value);
    void set_float(const std::string &name, float value);
    void set_mat4(const std::string &name, const glm::mat4 & mat);

    unsigned int get_id() { return id_; };
private:
    unsigned int id_ = 0;

    bool check_compilation(unsigned int shader, std::string type);
};
