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
    static const int PLAYER_TAG = 0;
    static const int BOUNDARY_TAG = 1;

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
    Add keyboard event listener.
    Author: ChuyangLiu
    */
    void addKeyboardListener();

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
