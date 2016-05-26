#ifndef __HOMESCENE_H__
#define __HOMESCENE_H__

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
    Initialize start button.
    Author: ChuyangLiu
    */
    void initStartBtn();
};

#endif
