#pragma once

#include "EnemySprite.h"
#include "PlayerBulletSprite.h"
#include "EnemyBulletSprite.h"

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
    Add boundary physics body.
    Author: ChuyangLiu
    */
    void addBoundary();

    /*
    Add player.
    Author: ChuyangLiu
    */
    void addPlayer();

    /*
    Add enemy.
    Author: ChuyangLiu
    */
    void addEnemey();

    /*
    Add walls.
    Author: ChuyangLiu
    */
    void addWall();

    /*
    Add keyboard event listener.
    Author: ChuyangLiu
    */
    void addKeyboardListener();

    /*
    Add mouse event listener.
    Author: ChuyangLiu
    */
    void addMouseListener();

    /*
    Add physics body contact event listener.
    Author: ChuyangLiu
    */
    void addContactListener();

    /*
    Called when the player hits an enemy.
    Author: ChuyangLiu
    */
    void meetPlayerWithEnemy(EnemySprite *enemy);

    /*
    Called when the player hits an enemy bullet.
    Author: ChuyangLiu
    */
    void meetPlayerWithEnemyBullet(EnemyBulletSprite *enemyBullet);

    /*
    Called when the player hits an enemy bullet.
    Author: ChuyangLiu
    */
    void meetEnemyWithPlayerBullet(EnemySprite *enemy, PlayerBulletSprite *playerBullet);

    /*
    Called when the player hits the wall.
    Author: ChuyangLiu
    */
    void meetPlayerWithWall(PlayerSprite *player);

    /*
    Called when the player hits the wall.
    Author: ChuyangLiu
    */
    void meetEnemyWithWall(EnemySprite *enemy);

    /*
    Callback for schedule.
    Author: ChuyangLiu
    */
    void update(float f);
};
