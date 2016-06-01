#pragma once

#include "EnemySpriteBase.h"

/*
An enemy sprite
*/
class EnemySprite : public EnemySpriteBase {
public:
    /*
    Create an enemy sprite.
    Author: ChuyangLiu
    */
    static EnemySprite* create(cocos2d::Layer *layer = nullptr);

private:

    /*
    Inaccessible default constructor from outside the class.
    Use create() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    EnemySprite() {}

    /*
    Enemy fire at the target.
    Author: ChuyangLiu
    */
    virtual void fire(const cocos2d::Vec2 &target);

    /*
    Make an AI decision.
    Author: ChuyangLiu
    */
    virtual void makeAIDecision();
};
