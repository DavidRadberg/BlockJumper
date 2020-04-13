
#pragma once

#include <string>

enum MESHES { MARIO };

class Meshes {
public:
    static constexpr char const * get_obj_path(MESHES mesh) {
        switch(mesh) {
            case MESHES::MARIO:
                return "../data/obj/Obj/Mario.obj";
            default:
                return "../data/obj/Obj/Mario.obj";
        }
    };
};
