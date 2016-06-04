#pragma once

#include "AliveSpriteBase.h"
#include "GameUtil.h"
#include "SpriteBase.h"

class PlayerSpriteBase : public AliveSpriteBase, public SpriteBase {
public:
    PlayerSpriteBase();
    virtual ~PlayerSpriteBase();

    /*
    Set the move value of the player towards the direction.
    Author: ChuyangLiu
    */
    virtual void setMoveVal(const Direction &direc) = 0;

    /*
    Reset the move value of the player towards the direction.
    Author: ChuyangLiu
    */
    virtual void resetMoveVal(const Direction &direc) = 0;

    /*
    Player fire at the target.
    Author: ChuyangLiu
    */
    virtual void fire(cocos2d::Layer *layer, const cocos2d::Vec2 *target = nullptr) = 0;

private:
};
