#pragma once

/*
Store constants.
*/
class Constants {
public:
    static const int PLAYER_MOVE_DIST = 5;
    static const int PLAYER_BULLET_SPEED = 300;

    // PhysicsBody groups and bitmasks
    static const int BOUND_PHYSIC_GROUP = 1;
    static const int BOUND_PHYSIC_CATEGORY_BM = 0x00000001;
    static const int BOUND_PHYSIC_COLLISION_BM = 0x0000001;
    static const int BOUND_PHYSIC_CONTACT_BM = 0x00000000;
    static const int PLAYER_PHYSIC_GROUP = -1;
    static const int PLAYER_PHYSIC_CATEGORY_BM = 0x00000001;
    static const int PLAYER_PHYSIC_COLLISION_BM = 0x0000000;
    static const int PLAYER_PHYSIC_CONTACT_BM = 0x00000010;
    static const int PLAYER_BULLET_PHYSIC_GROUP = -1;
    static const int PLAYER_BULLET_PHYSIC_CATEGORY_BM = 0x00000001;
    static const int PLAYER_BULLET_PHYSIC_COLLISION_BM = 0x0000001;
    static const int PLAYER_BULLET_PHYSIC_CONTACT_BM = 0x00000010;
};
