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
    void addEnemy();

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
    void meetPlayerWithEnemy(PlayerSprite *plyr, EnemySpriteBase *enemy);

    /*
    Called when the player hits an enemy bullet.
    Author: ChuyangLiu
    */
    void meetPlayerWithEnemyBullet(PlayerSprite *plyr, EnemyBulletSprite *enemyBullet);

    /*
    Called when the player hits an enemy bullet.
    Author: ChuyangLiu
    */
    void meetEnemyWithPlayerBullet(EnemySpriteBase *enemy, PlayerBulletSprite *playerBullet);

    /*
    Called when the player hits the wall.
    Author: ChuyangLiu
    */
    void meetPlayerWithWall(PlayerSprite *plyr, WallSprite *wall);

    /*
    Called when the player hits the wall.
    Author: ChuyangLiu
    */
    void meetEnemyWithWall(EnemySpriteBase *enemy, WallSprite *wall);

    /*
    Called when the player bullet hits the wall.
    Author: ChuyangLiu
    */
    void meetPlayerBulletWithWall(PlayerBulletSprite *playerBullet, WallSprite *wall);

    /*
    Called when the player bullet hits the wall.
    Author: ChuyangLiu
    */
    void meetEnemyBulletWithWall(EnemyBulletSprite *enemyBullet, WallSprite *wall);

    /*
    Callback for schedule.
    Author: ChuyangLiu
    */
    void update(float f);

	/*
	Add the green background.
	Author: YifengWong
	*/
	void addBackground();

	/*
	Add the boss.
	Author: YifengWong
	*/
	void addBoss();
};
