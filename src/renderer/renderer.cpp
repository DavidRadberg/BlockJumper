#include "renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "spdlog/spdlog.h"

#include <iostream>
#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(Camera & camera) : camera_(camera)
{
    spdlog::info("Initializing Renderer...");
    assert(shader_.compile_shader("../shaders/basic.vert.glsl", "../shaders/basic.frag.glsl"));

    float tmp_vertices[] = {
        0.0,  0.0, 0.0,
        1.0,  0.0, 0.0,
        1.0,  1.0, 0.0,
        0.0,  1.0, 0.0,

        0.0,  0.0, 1.0,
        1.0,  0.0, 1.0,
        1.0,  1.0, 1.0,
        0.0,  1.0, 1.0,

        0.0,  0.0, 1.0,
        1.0,  0.0, 1.0,
        1.0,  1.0, 1.0,
        0.0,  1.0, 1.0
    };

    for (float v : tmp_vertices) {
        vertices_.push_back(v);
    }

    float tmp_uv[] = {
        0.0,  0.0,
        1.0,  0.0,
        1.0,  1.0,
        0.0,  1.0,

        1.0,  0.0,
        2.0,  0.0,
        2.0,  1.0,
        1.0,  1.0,

        0.0, -1.0,
        1.0, -1.0,
        1.0,  2.0,
        0.0,  2.0
    };

    for (float uv : tmp_uv) {
        uv_.push_back(uv);
    }

    unsigned int tmp_indices[] = {
        // sides
        0, 1, 2,
        2, 3, 0,

        1, 5, 6,
        6, 2, 1,

        5, 4, 7,
        7, 6, 5,

        4, 0, 3,
        3, 7, 4,

        // top and bottom
        8, 9, 1,
        1, 0, 8,

        3, 2, 10,
        10, 11, 3
    };

    for (int i : tmp_indices) {
        indices_.push_back(i);
    }

    spdlog::info("Creating buffers...");

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_pos_);
    glGenBuffers(1, &vbo_uv_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_uv_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * uv_.size(), uv_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices_.size(), indices_.data(), GL_STATIC_DRAW);

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
    unsigned char *data = stbi_load("../data/textures/brick_wall.png", &width, &height, &nrChannels, 0);
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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void Renderer::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_);

    const glm::mat4 mvp = camera_.get_mvp();

    shader_.run();
    shader_.set_mat4("MVP", mvp);

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
