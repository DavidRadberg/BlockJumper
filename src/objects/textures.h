
#pragma once

#include <string>

enum TEXTURES { BRICK, SAND, GRASS, BLUE, GRANITE, STONE, MARIO_MAIN };

class Textures {
public:
    static constexpr char const * get_texture_path(TEXTURES texture) {
        switch(texture) {
            case TEXTURES::BRICK:
                return "../data/textures/brick_wall.png";
            case TEXTURES::SAND:
                return "../data/textures/sand.png";
            case TEXTURES::GRASS:
                return "../data/textures/grass.png";
            case TEXTURES::BLUE:
                return "../data/textures/blue.jpg";
            case TEXTURES::GRANITE:
                return "../data/textures/granite.jpg";
            case TEXTURES::STONE:
                return "../data/textures/stone.jpg";
            case TEXTURES::MARIO_MAIN:
                return "../data/obj/Textures/mario_main.png";
            default:
                return "../data/textures/grass.png";
        }
    };
};
