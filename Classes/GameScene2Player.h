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

	/*
	Return the player sprite.
	Author: ChuyangLiu
	*/
	static PlayerDualSprite* getPlayer_1();
	static PlayerDualSprite* getPlayer_2();

private:
	static PlayerDualSprite *player_1;
	static PlayerDualSprite *player_2;

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
	void meetPlayerWithEnemy(PlayerDualSprite *plyr, EnemySpriteBase *enemy);
	void meetPlayerWithEnemyBullet(PlayerDualSprite *plyr, EnemyBulletSprite *enemyBullet);
	void meetEnemyWithPlayerBullet(EnemySpriteBase *enemy, PlayerBulletSprite *playerBullet);
	void meetPlayerWithWall(PlayerDualSprite *plyr, WallSprite *wall);
	void meetEnemyWithWall(EnemySpriteBase *enemy, WallSprite *wall);
	void meetBulletWithWall(PlayerBulletSprite *playerBullet, WallSprite *wall);
	void meetEnemyBulletWithWall(EnemyBulletSprite *enemyBullet, WallSprite *wall);

	/*
	Callback for schedule.
	Author: ChuyangLiu
	*/
	void update(float f);
};
