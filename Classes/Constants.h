#pragma once

/*
Store constants.
*/
class Constants {
public:
    static const int PLAYER_MOVE_DIST = 200;

    // PhysicsBody groups and bitmasks
    static const int BOUND_PHYSIC_GROUP = 1;
    static const int BOUND_PHYSIC_CATEGORY_BM = 0x00000002;
    static const int BOUND_PHYSIC_CONTACT_BM = 0x00000001;
    static const int PLAYER_PHYSIC_GROUP = 1;
    static const int PLAYER_PHYSIC_CATEGORY_BM = 0x00000001;
    static const int PLAYER_PHYSIC_CONTACT_BM = 0x00000002;
};
