#pragma once

#include "PlayerBulletSprite.h"
#include "EnemyBulletSprite.h"
#include "WallSprite.h"
#include "PlayerSingleSprite.h"
#include "EnemySpriteBase.h"

/*
Game Scene for one player
*/
class GameScene1Player : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene1Player);

    /*
    Return the player sprite.
    Author: ChuyangLiu
    */
    static PlayerSingleSprite* GameScene1Player::getPlayer();

private:
    static PlayerSingleSprite *player;

    /*
    Inaccessible default constructor from outside the class.
    Use createScene() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    GameScene1Player() {}

    /*
    Add sprites.
    Author: ChuyangLiu & YifengWong
    */
    void addBackground();
    void addBoundary();
    void addPlayer();
    void addEnemies();
    void addWalls();

    /*
    Add event listeners.
    Author: ChuyangLiu
    */
    void addKeyboardListener();
    void addMouseListener();
    void addContactListener();

    /*
    Meet events
    Author: ChuyangLiu
    */
    void meetPlayerWithEnemy(PlayerSingleSprite *plyr, EnemySpriteBase *enemy);
    void meetPlayerWithEnemyBullet(PlayerSingleSprite *plyr, EnemyBulletSprite *enemyBullet);
    void meetEnemyWithPlayerBullet(EnemySpriteBase *enemy, PlayerBulletSprite *playerBullet);
    void meetPlayerWithWall(PlayerSingleSprite *plyr, WallSprite *wall);
    void meetEnemyWithWall(EnemySpriteBase *enemy, WallSprite *wall);
    void meetBulletWithWall(BulletSpriteBase *bullet, WallSprite *wall);

    /*
    Callback for schedule.
    Author: ChuyangLiu
    */
    void update(float f);
};
