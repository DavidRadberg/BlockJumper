#pragma once

enum CharacterActions { STANDING, JUMPING, FALLING };

struct CharacterState {
public:
    float t = 0.0;
    float dt = 0.0;
    float speed = 0.0;
    CharacterActions action = CharacterActions::STANDING;

    bool is_standing() const { return action == CharacterActions::STANDING; };
    bool is_jumping() const { return action == CharacterActions::JUMPING; };
    bool is_falling() const { return action == CharacterActions::FALLING; };
    bool is_running() const { return action == CharacterActions::STANDING && speed > 0.0; };
};
