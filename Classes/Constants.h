#pragma once

#include <bitset>

class Constants {
public:
    static const int PLAYER_MOVE_DIST = 5;
    static const int ENEMY_MOVE_DIST = 50;
    static const int PLAYER_BULLET_SPEED = 200;
    static const int BULLET_LAST_TIME = 2;

    // Debug switchers
    static const bool DRAW_WORLD_EDGE = true;

    /*
    Six types of the sprite:
    1. Player     2.PlayerBullet    3.Boundary
    4. Enemy      5.EnemyBullet     6.Wall
    (ps. using Bullet = { PlayerBullet | EnemyBullet })

    Collision events requirements:
    Object:                 Collide:   Trigger collision event:
    [Bullet, Bullet]        false      don't care
    [Bullet, Boundary]      true       false
    [Bullet, Wall]          true       false
    [Player, PlayerBullet]  false      don't care
    [Player, EnemyBullet]   true       true
    [Player, Boundary]      false      don't care
    [Player, Wall]          true       false
    [Player, Enemy]         true       true
    [Enemy,  PlayerBullet]  true       true
    [Enemy,  EnemyBullet]   false      don't care
    [Enemy,  Boundary]      true       false
    [Enemy,  Wall]          true       false
    */

    // PhysicBody tag
    static const int PLAYER_TAG = 0;
    static const int ENEMY_TAG = 1;
    static const int BULLET_PLAYER_TAG = 2;
    static const int BULLET_ENEMY_TAG = 3;
    static const int BOUNDARY_TAG = 4;
    static const int WALL_TAG = 5;

    // Boundary physic groups and bitmasks
    static const int BOUND_PHYSIC_GROUP = 1;
    static const int BOUND_PHYSIC_CATEGORY_BM = 0x0000001;   // 0001
    static const int BOUND_PHYSIC_COLLISION_BM = 0x0000002;  // 0010
    static const int BOUND_PHYSIC_CONTACT_BM = 0x00000000;   // 0000
    // Wall physic groups and bitmasks
    static const int WALL_PHYSIC_GROUP = 1;
    static const int WALL_PHYSIC_CATEGORY_BM = 0x0000001;   // 0001
    static const int WALL_PHYSIC_COLLISION_BM = 0x0000002;  // 0110
    static const int WALL_PHYSIC_CONTACT_BM = 0x00000000;   // 0000
    // Player physic groups and bitmasks
    static const int PLAYER_PHYSIC_GROUP = 2;
    static const int PLAYER_PHYSIC_CATEGORY_BM = 0x00000001;  // 0001
    static const int PLAYER_PHYSIC_COLLISION_BM = 0x0000004;  // 0101
    static const int PLAYER_PHYSIC_CONTACT_BM = 0x00000003;   // 0011
    // Enemy physic groups and bitmasks
    static const int ENEMY_PHYSIC_GROUP = 2;
    static const int ENEMY_PHYSIC_CATEGORY_BM = 0x00000001;
    static const int ENEMY_PHYSIC_COLLISION_BM = 0x0000000;
    static const int ENEMY_PHYSIC_CONTACT_BM = 0x00000010;
    // Player bullet physic groups and bitmasks
    static const int BULLET_PLAYER_PHYSIC_GROUP = -1;
    static const int BULLET_PLAYER_PHYSIC_CATEGORY_BM = 0x00000010;  // 0010
    static const int BULLET_PLAYER_PHYSIC_COLLISION_BM = 0x0000001;  // 0001
    static const int BULLET_PLAYER_PHYSIC_CONTACT_BM = 0x00000010;
    // Enemy bullet physic groups and bitmasks
    static const int BULLET_ENEMY_PHYSIC_GROUP = -1;
    static const int BULLET_ENEMY_PHYSIC_CATEGORY_BM = 0x00000003;  // 0011
    static const int BULLET_ENEMY_PHYSIC_COLLISION_BM = 0x0000005;  // 0101
    static const int BULLET_ENEMY_PHYSIC_CONTACT_BM = 0x00000001;   // 0001
};
