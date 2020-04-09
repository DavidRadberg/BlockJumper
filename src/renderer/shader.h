#pragma once

#include <string>

class Shader {
public:
    void compile_shader(const char* vertexPath, const char* fragmentPath);
    void run();

    void set_bool(const std::string &name, bool value);
    void set_int(const std::string &name, int value);
    void set_float(const std::string &name, float value);
private:
    unsigned int ID = 0;

    void checkCompileErrors(unsigned int shader, std::string type);
};
