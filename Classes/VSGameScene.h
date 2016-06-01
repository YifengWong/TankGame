#pragma once

#include "PlayerBulletSprite.h"
#include "EnemyBulletSprite.h"
#include "WallSprite.h"
#include "VSPlayerSprite.h"
#include "EnemySpriteBase.h"

/*
Game Scene
*/
class VSGameScene : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(VSGameScene);

	/*
	Return the player sprite.
	Author: ChuyangLiu
	*/
	static VSPlayerSprite* getPlayer_1();
	static VSPlayerSprite* getPlayer_2();

private:
	static VSPlayerSprite *player_1;
	static VSPlayerSprite *player_2;

	/*
	Inaccessible default constructor from outside the class.
	Use createScene() to create the instance from outside the class.
	Author: ChuyangLiu
	*/
	VSGameScene() {}

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
	void meetPlayerWithEnemy(VSPlayerSprite *plyr, EnemySpriteBase *enemy);
	void meetPlayerWithEnemyBullet(VSPlayerSprite *plyr, EnemyBulletSprite *enemyBullet);
	void meetEnemyWithPlayerBullet(EnemySpriteBase *enemy, PlayerBulletSprite *playerBullet);
	void meetPlayerWithWall(VSPlayerSprite *plyr, WallSprite *wall);
	void meetEnemyWithWall(EnemySpriteBase *enemy, WallSprite *wall);
	void meetPlayerBulletWithWall(PlayerBulletSprite *playerBullet, WallSprite *wall);
	void meetEnemyBulletWithWall(EnemyBulletSprite *enemyBullet, WallSprite *wall);

	/*
	Callback for schedule.
	Author: ChuyangLiu
	*/
	void update(float f);
};
