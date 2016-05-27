#pragma once

/*
Store constants.
*/
class Constants {
public:
    static const int PLAYER_MOVE_DIST = 5;
    static const int PLAYER_BULLET_SPEED = 300;
    static const int BULLET_LAST_TIME = 3;

    // Debug switchers
    static const bool DRAW_WORLD_EDGE = true;

    // Boundary physic groups and bitmasks
    static const int BOUND_PHYSIC_GROUP = 1;
    static const int BOUND_PHYSIC_CATEGORY_BM = 0x00000001;
    static const int BOUND_PHYSIC_COLLISION_BM = 0x0000001;
    static const int BOUND_PHYSIC_CONTACT_BM = 0x00000000;
    // Player physic groups and bitmasks
    static const int PLAYER_PHYSIC_GROUP = -1;
    static const int PLAYER_PHYSIC_CATEGORY_BM = 0x00000001;
    static const int PLAYER_PHYSIC_COLLISION_BM = 0x0000000;
    static const int PLAYER_PHYSIC_CONTACT_BM = 0x00000010;
    // Player bullet physic groups and bitmasks
    static const int BULLET_PLAYER_PHYSIC_GROUP = -1;
    static const int BULLET_PLAYER_PHYSIC_CATEGORY_BM = 0x00000001;
    static const int BULLET_PLAYER_PHYSIC_COLLISION_BM = 0x0000001;
    static const int BULLET_PLAYER_PHYSIC_CONTACT_BM = 0x00000010;
    // Enemy bullet physic groups and bitmasks
    static const int BULLET_ENEMY_PHYSIC_GROUP = -1;
    static const int BULLET_ENEMY_PHYSIC_CATEGORY_BM = 0x00000001;
    static const int BULLET_ENEMY_PHYSIC_COLLISION_BM = 0x0000001;
    static const int BULLET_ENEMY_PHYSIC_CONTACT_BM = 0x00000010;
};
