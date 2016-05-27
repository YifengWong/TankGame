#pragma once

#include "PlayerSprite.h"

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
    Callback for schedule.
    Author: ChuyangLiu
    */
    void update(float f);
};
