#include "renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "spdlog/spdlog.h"

#include <iostream>
#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(const Camera & camera, Object & object)
    : camera_(camera), object_(object)
{
    spdlog::info("Initializing Renderer...");
    assert(shader_.compile_shader("../shaders/basic.vert.glsl", "../shaders/basic.frag.glsl"));

    spdlog::info("Creating buffers...");

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_pos_);
    glGenBuffers(1, &vbo_uv_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * object_.get_vertices().size(), object_.get_vertices().data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_uv_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * object_.get_uv().size(), object_.get_uv().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * object_.get_indices().size(), object_.get_indices().data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    spdlog::info("Creating texture...");
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(object_.get_texture_path(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        spdlog::critical("Loading texture failed!");
        assert(0);
    }
    stbi_image_free(data);

    shader_.run();
    glUniform1i(glGetUniformLocation(shader_.get_id(), "aTex"), 0);

    glBindTexture(GL_TEXTURE_2D, 0);


}

void Renderer::render()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * object_.get_vertices().size(), object_.get_vertices().data(), GL_DYNAMIC_DRAW);

    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, texture_);

    const glm::mat4 mvp = camera_.get_mvp();

    shader_.run();
    shader_.set_mat4("MVP", mvp);

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, object_.get_indices().size(), GL_UNSIGNED_INT, 0);
}
