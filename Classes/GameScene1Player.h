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
    Return the player sprite
    Author: ChuyangLiu
    */
    const PlayerSingleSprite* getPlayer() const;

    /*
    Show widgets
    Author: ChuyangLiu
    */
    void showGameoverBtn();
    void showNextBtn();
    void showWinBtn();

    /*
    Decrease the enemy count and check if the player
    can go to next checkpoint
    Author: ChuyangLiu
    */
    void decreaseEnemyCnt();

private:
    unsigned enemyCnt = 0;

    PlayerSingleSprite *player = nullptr;
    cocos2d::ui::Button *gameoverBtn = nullptr;
    cocos2d::ui::Button *nextBtn = nullptr;
    cocos2d::ui::Button *winBtn = nullptr;


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
    void addGameInfo();

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

    /*
    Check if there is one game info label shown
    Author: ChuyangLiu
    */
    bool isOneInfoShown() const;
};
