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
private:
    PlayerSprite *player = NULL;

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
    void meetPlayerWithEnemy(PlayerSprite *player, EnemySprite *enemy);

    /*
    Called when the player hits an enemy bullet.
    Author: ChuyangLiu
    */
    void meetPlayerWithEnemyBullet(PlayerSprite *player, EnemyBulletSprite *enemyBullet);

    /*
    Called when the player hits an enemy bullet.
    Author: ChuyangLiu
    */
    void meetEnemyWithPlayerBullet(EnemySprite *enemy, PlayerBulletSprite *playerBullet);

    /*
    Callback for schedule.
    Author: ChuyangLiu
    */
    void update(float f);
};
