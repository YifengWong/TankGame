#pragma once

/*
Game Scene
*/
class GameScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
private:
    /*
    Add edge physics body.
    Author: ChuyangLiu
    */
    void addEdge();
};
