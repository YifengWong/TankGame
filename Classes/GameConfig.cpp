#include "GameConfig.h"

unsigned GameConfig::CURRENT_STAGE = 0;

// Bullet common config
int GameConfig::BULLET_DAMAGE = 100;
int GameConfig::BULLET_LAST_TIME = 4;  // Seconds

// Enemy common config
int GameConfig::ENEMY_DECISION_INTERVAL = 1;  // Seconds

// Player config
int GameConfig::PLAYER_MOVE_SPEED = 100;
int GameConfig::PLAYER_BULLET_SPEED = 150;
unsigned GameConfig::PLAYER_BULLET_NUM_LIMIT = 5;
int GameConfig::PLAYER_INIT_HP = 1000;
int GameConfig::PLAYER_MAX_HP = 1000;

// Normal enemy config
int GameConfig::ENEMY_NORMAL_MOVE_SPEED = 50;
int GameConfig::ENEMY_NORMAL_BULLET_SPEED = 150;
int GameConfig::ENEMY_NORMAL_COLLISION_DAMAGE = 300;
int GameConfig::ENEMY_NORMAL_MAX_HP = 1000;
int GameConfig::ENEMY_NORMAL_INIT_HP = 1000;

// Boss enemy config
int GameConfig::ENEMY_BOSS_MOVE_SPEED = 100;
int GameConfig::ENEMY_BOSS_BULLET_SPEED = 200;
int GameConfig::ENEMY_BOSS_COLLISION_DAMAGE = 500;
int GameConfig::ENEMY_BOSS_MAX_HP = 2000;
int GameConfig::ENEMY_BOSS_INIT_HP = 2000;

// Music
bool GameConfig::MUTE = false;
float GameConfig::MUSIC_BG_VOLUME = 0.2f;      // Value must between 0 and 1
float GameConfig::MUSIC_EFFECT_VOLUME = 0.1f;  // Value must between 0 and 1
