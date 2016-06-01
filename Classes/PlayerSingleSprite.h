#pragma once

#include "PlayerSpriteBase.h"

/*
A player sprite for single player model
*/
class PlayerSingleSprite : public PlayerSpriteBase {
public:
    /*
    Create a player sprite.
    Author: ChuyangLiu
    */
    static PlayerSingleSprite* create();

    /*
    Set the move value of the player towards the direction.
    Author: ChuyangLiu
    */
    virtual void setMoveVal(const Direction &direc) override;

    /*
    Reset the move value of the player towards the direction.
    Author: ChuyangLiu
    */
    virtual void resetMoveVal(const Direction &direc) override;

    /*
    Player fire at the target.
    Author: ChuyangLiu
    */
    virtual void fire(cocos2d::Layer *layer, const cocos2d::Vec2 *target = nullptr) override;

private:
    /*
    Inaccessible default constructor from outside the class.
    Use create() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    PlayerSingleSprite() {}
};
