#pragma once

#include "LayoutUtil.h"
#include "HPValue.h"

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

    /*
    Check if the player is dead.
    Author: ChuyangLiu
    */
    bool isDead();

    /*
    Return the hp value.
    Author: ChuyangLiu
    */
    HPValue* getHP();

private:
    HPValue hp;

    /*
    Inaccessible default constructor from outside the class.
    Use create() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    PlayerSprite() {}

    /*
    Set the hp value.
    Author: ChuyangLiu
    */
    void setHP(const int hp);
};
