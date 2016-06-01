#pragma once

#include "PlayerBulletSprite.h"
#include "EnemyBulletSprite.h"
#include "WallSprite.h"
#include "PlayerSprite.h"
#include "EnemySpriteBase.h"

/*
Game Scene
*/
class GameScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

    /*
    Return the player sprite.
    Author: ChuyangLiu
    */
    static PlayerSprite* getPlayer();

private:
    static PlayerSprite *player;

    /*
    Inaccessible default constructor from outside the class.
    Use createScene() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    GameScene() {}

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
    void meetPlayerWithEnemy(PlayerSprite *plyr, EnemySpriteBase *enemy);
    void meetPlayerWithEnemyBullet(PlayerSprite *plyr, EnemyBulletSprite *enemyBullet);
    void meetEnemyWithPlayerBullet(EnemySpriteBase *enemy, PlayerBulletSprite *playerBullet);
    void meetPlayerWithWall(PlayerSprite *plyr, WallSprite *wall);
    void meetEnemyWithWall(EnemySpriteBase *enemy, WallSprite *wall);
    void meetPlayerBulletWithWall(PlayerBulletSprite *playerBullet, WallSprite *wall);
    void meetEnemyBulletWithWall(EnemyBulletSprite *enemyBullet, WallSprite *wall);

    /*
    Callback for schedule.
    Author: ChuyangLiu
    */
    void update(float f);
};
