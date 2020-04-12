
#pragma once

#include <string>

enum TEXTURES { BRICK_TEXTURE };

class Textures {
public:
    static constexpr char const * get_texture_path(TEXTURES texture) {
        switch(texture) {
            case TEXTURES::BRICK_TEXTURE:
                return "../data/textures/brick_wall.png";
            default:
                return "../data/textures/brick_wall.png";
        }
    };
};
