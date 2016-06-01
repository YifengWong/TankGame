#pragma once

class GameConfig {
public:
    // Bullet common config
    static const int BULLET_DAMAGE = 100;
    static const int BULLET_LAST_TIME = 3;

    // Enemy common config
    static const int ENEMY_DECISION_INTERVAL = 1;

    // Player config
    static const int PLAYER_MOVE_SPEED = 100;
    static const int PLAYER_BULLET_SPEED = 150;
    static const int PLAYER_BULLET_NUM_LIMIT = 5;
    static const int PLAYER_INIT_HP = 1000;
    static const int PLAYER_MAX_HP = 1000;

    // Normal enemy config
    static const int ENEMY_NORMAL_MOVE_SPEED = 50;
    static const int ENEMY_NORMAL_BULLET_SPEED = 150;
    static const int ENEMY_NORMAL_COLLISION_DAMAGE = 300;
    static const int ENEMY_NORMAL_MAX_HP = 1000;
    static const int ENEMY_NORMAL_INIT_HP = 1000;

    // Boss enemy config
    static const int ENEMY_BOSS_MOVE_SPEED = 100;
    static const int ENEMY_BOSS_BULLET_SPEED = 200;
    static const int ENEMY_BOSS_COLLISION_DAMAGE = 500;
    static const int ENEMY_BOSS_MAX_HP = 2000;
    static const int ENEMY_BOSS_INIT_HP = 2000;

    // Debug switchers
    static const bool DRAW_WORLD_EDGE = false;

    /*
    Five types of the sprite:
    1. Player   2. PlayerBullet   3. Wall
    4. Enemy    5. EnemyBullet
    
    abbr. using Bullet = (PlayerBullet && EnemyBullet)
          using      X = "Don't care"

    Collision events requirements:
    Object:                  Collide:   Trigger collision event:
    [Bullet, Bullet]         false      X
    [Bullet, Wall]           true       true
    [Player, Player]         false      X
    [Player, PlayerBullet]   false      X
    [Player, EnemyBullet]    true       true
    [Player, Wall]           true       true
    [Player, Enemy]          true       true
    [Enemy,  Enemy]          false      X
    [Enemy,  PlayerBullet]   true       true
    [Enemy,  EnemyBullet]    false      X
    [Enemy,  Wall]           true       true
    */

    // PhysicBody tag
    static const int PLAYER_TAG = 0;
    static const int ENEMY_TAG = 1;
    static const int BULLET_PLAYER_TAG = 2;
    static const int BULLET_ENEMY_TAG = 3;
    static const int WALL_TAG = 4;

    // Wall physic groups and bitmasks
    static const int WALL_PHYSIC_GROUP = -3;
    static const int WALL_PHYSIC_CATEGORY_BM = 0x00000001;
    static const int WALL_PHYSIC_COLLISION_BM = 0x0000001F;
    static const int WALL_PHYSIC_CONTACT_BM = 0x0000001E;
    // Player physic groups and bitmasks
    static const int PLAYER_PHYSIC_GROUP = -4;
    static const int PLAYER_PHYSIC_CATEGORY_BM = 0x00000004;
    static const int PLAYER_PHYSIC_COLLISION_BM = 0x00000019;
    static const int PLAYER_PHYSIC_CONTACT_BM = 0x00000019;
    // Enemy physic groups and bitmasks
    static const int ENEMY_PHYSIC_GROUP = -2;
    static const int ENEMY_PHYSIC_CATEGORY_BM = 0x00000010;
    static const int ENEMY_PHYSIC_COLLISION_BM = 0x0000007;
    static const int ENEMY_PHYSIC_CONTACT_BM = 0x00000007;
    // Player bullet physic groups and bitmasks
    static const int BULLET_PLAYER_PHYSIC_GROUP = -1;
    static const int BULLET_PLAYER_PHYSIC_CATEGORY_BM = 0x00000002;
    static const int BULLET_PLAYER_PHYSIC_COLLISION_BM = 0x0000011;
    static const int BULLET_PLAYER_PHYSIC_CONTACT_BM = 0x00000011;
    // Enemy bullet physic groups and bitmasks
    static const int BULLET_ENEMY_PHYSIC_GROUP = -1;
    static const int BULLET_ENEMY_PHYSIC_CATEGORY_BM = 0x00000008;
    static const int BULLET_ENEMY_PHYSIC_COLLISION_BM = 0x0000005;
    static const int BULLET_ENEMY_PHYSIC_CONTACT_BM = 0x00000005;
};
