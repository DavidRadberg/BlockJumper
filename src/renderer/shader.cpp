
#include "shader.h"
#include "spdlog/spdlog.h"

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


bool Shader::compile_shader(const char* vertexPath, const char* fragmentPath) {
    spdlog::info("Compiling shader...");

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        spdlog::critical("Shader error file read unsuccessful!");
        return false;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    if (!check_compilation(vertex, "VERTEX")) {
        return false;
    }
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    if (!check_compilation(fragment, "FRAGMENT")) {
        return false;
    }
    // shader Program
    id_ = glCreateProgram();
    glAttachShader(id_, vertex);
    glAttachShader(id_, fragment);
    glLinkProgram(id_);
    if (!check_compilation(id_, "PROGRAM")) {
        return false;
    }
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return true;
}

void Shader::run() { 
    glUseProgram(id_); 
}

void Shader::set_bool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
}

void Shader::set_int(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
}

void Shader::set_float(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(id_, name.c_str()), (float)value);
}

void Shader::set_mat4(const std::string &name, const glm::mat4 & mat) {
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


bool Shader::check_compilation(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            spdlog::critical("Compilation of shader unsuccessful!\n {}", infoLog);
            return false;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            spdlog::critical("Compilation of program unsuccessful!\n {}", infoLog);
            return false;
        }
    }
    return true;
}
