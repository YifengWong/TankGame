#pragma once

#include "PlayerSprite.h"

/*
An enemey sprite
*/
class EnemySprite : public cocos2d::Sprite {
public:
    /*
    Create an enemy sprite.
    Author: ChuyangLiu
    */
    static EnemySprite* create(cocos2d::Layer *layer);

private:
    cocos2d::Layer *layer = nullptr;

    /*
    Inaccessible default constructor from outside the class.
    Use create() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    EnemySprite() {}

    /*
    Set the layer of the enemy.
    Author: ChuyangLiu
    */
    void setLayer(cocos2d::Layer *layer_);

    /*
    Schedule the enemy AI.
    Author: ChuyangLiu
    */
    void scheduleAI();

    /*
    Enemy fire at the target.
    Author: ChuyangLiu
    */
    void fire(const cocos2d::Vec2 &target);
};
