
#pragma once

#include "object.h"
#include "meshes.h"
#include "textures.h"

#include <glm/glm.hpp>

class Mesh : public Object {
public:
    Mesh(MESHES mesh, TEXTURES texture);

    void transpose(const glm::vec3 & diff);

private:
    void update_bb();
};