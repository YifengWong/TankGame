#pragma once

#include "PlayerBulletSprite.h"
#include "EnemyBulletSprite.h"
#include "WallSprite.h"
#include "PlayerDualSprite.h"
#include "EnemySpriteBase.h"

/*
Game Scene for two players
*/
class GameScene2Player : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene2Player);


	static PlayerDualSprite *player_1;
	static PlayerDualSprite *player_2;

private:
	
	/*
	Inaccessible default constructor from outside the class.
	Use createScene() to create the instance from outside the class.
	Author: ChuyangLiu
	*/
	GameScene2Player() {}

	/*
	Add sprites.
	Author: ChuyangLiu & YifengWong
	*/
	void addBackground();
	void addBoundary();
	void addPlayer();
	void addWalls();

	/*
	Add event listeners.
	Author: ChuyangLiu
	*/
	void addKeyboardListener();
	void addContactListener();

	/*
	Meet events
	Author: ChuyangLiu
	*/
	void meetPlayerWithEnemy(PlayerDualSprite *plyr, PlayerDualSprite *enemy);
	void meetPlayerWithEnemyBullet(PlayerDualSprite *plyr, EnemyBulletSprite *enemyBullet);
	void meetEnemyWithPlayerBullet(PlayerDualSprite *enemy, PlayerBulletSprite *playerBullet);
	void meetPlayerWithWall(PlayerDualSprite *plyr, WallSprite *wall);
	void meetEnemyWithWall(PlayerDualSprite *enemy, WallSprite *wall);
	void meetBulletWithWall(PlayerBulletSprite *playerBullet, WallSprite *wall);
	void meetEnemyBulletWithWall(EnemyBulletSprite *enemyBullet, WallSprite *wall);

	/*
	Callback for schedule.
	Author: ChuyangLiu
	*/
	void update(float f);
};
