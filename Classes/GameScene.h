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
    Add edge physics body.
    Author: ChuyangLiu
    */
    void addEdge();

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
    Callback for schedule.
    Author: ChuyangLiu
    */
    void update(float f);
};
