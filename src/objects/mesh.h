
#pragma once

#include "object.h"
#include "meshes.h"
#include "textures.h"

#include <glm/glm.hpp>

class Mesh : public Object {
public:
    Mesh(MESHES mesh, TEXTURES texture);

private:
    float height_ = 2.0;
};