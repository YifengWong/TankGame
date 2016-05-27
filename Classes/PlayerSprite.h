#pragma once

#include "LayoutUtil.h"

/*
Player sprite: a subclass of cocos2d::sprite
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

private:
    // Move value of the player
    int moveX, moveY;
};
