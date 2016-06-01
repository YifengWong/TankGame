#pragma once

#include "AliveSpriteBase.h"

/*
Base class for an enemy sprite
*/
class EnemySpriteBase : public AliveSpriteBase {
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
};
