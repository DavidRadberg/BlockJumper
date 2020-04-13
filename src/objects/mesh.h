
#pragma once

#include "object.h"
#include "meshes.h"
#include "textures.h"



class Mesh : public Object {
public:
    Mesh(MESHES mesh, TEXTURES texture);
};