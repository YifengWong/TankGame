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
    Inaccessible default constructor from outside the class.
    Use createScene() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    HomeScene() {}

    /*
    Add start button to the layer.
    Author: ChuyangLiu
    */
    void addStartBtn();
};

