#pragma once

#include "LayoutUtil.h"

/*
A player sprite
*/
class PlayerSprite : public cocos2d::Sprite {
public:
    /*
    Create a player sprite.
    Author: ChuyangLiu
    */
    static PlayerSprite* create();

    /*
    Start moving by the move value.
    Author: ChuyangLiu
    */
    void move();

    /*
    Set the move value of the player towards the direction.
    Author: ChuyangLiu
    */
    void setMoveVal(const Direction &direc);

    /*
    Reset the move value of the player towards the direction.
    Author: ChuyangLiu
    */
    void resetMoveVal(const Direction &direc);

    /*
    Player fire at the target.
    Author: ChuyangLiu
    */
    void fire(cocos2d::Layer *layer, const cocos2d::Vec2 &target);

private:
    // Move value of the player
    int moveX, moveY;
};
