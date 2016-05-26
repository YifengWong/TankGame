#pragma once

/*
Home Scene
*/
class HomeScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HomeScene);
private:
    /*
    Add start button to the layer.
    Author: ChuyangLiu
    */
    void addStartBtn();
};

