#pragma once

#include "HPValue.h"

/*
Base class for an enemy sprite
*/
class EnemySpriteBase : public cocos2d::Sprite {
public:

    /*
    Enemy fire at the target.
    Author: ChuyangLiu
    */
    virtual void fire(const cocos2d::Vec2 &target) = 0;

    /*
    Make an AI decision.
    Author: ChuyangLiu
    */
    virtual void makeAIDecision() = 0;

    /*
    Check if the enemy is dead.
    Author: ChuyangLiu
    */
    bool isDead();

    /*
    Return the hp value.
    Author: ChuyangLiu
    */
    HPValue* getHP();

protected:
    /*
    Set the layer of the enemy.
    Author: ChuyangLiu
    */
    void setLayer(cocos2d::Layer *layer_);

    /*
    Return the layer of the enemy.
    Author: ChuyangLiu
    */
    cocos2d::Layer* getLayer();

    /*
    Run the enemy AI.
    Author: ChuyangLiu
    */
    void runAI();

private:
    // The layer of the enemy
    cocos2d::Layer *layer = nullptr;

    // The HP of the enemy
    HPValue hp;
};
