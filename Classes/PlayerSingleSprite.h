#pragma once

#include "PlayerSpriteBase.h"

class GameScene1Player;

/*
A player sprite for single player model
*/
class PlayerSingleSprite : public PlayerSpriteBase {
public:
    virtual ~PlayerSingleSprite();

    /*
    Create a player sprite.
    Author: ChuyangLiu
    */
    static PlayerSingleSprite* create(GameScene1Player *scene);

    /*
    Set the move value of the player towards the direction.
    Author: ChuyangLiu
    */
    virtual void setMoveVal(const GameUtil::Direction &direc) override;

    /*
    Reset the move value of the player towards the direction.
    Author: ChuyangLiu
    */
    virtual void resetMoveVal(const GameUtil::Direction &direc) override;

    /*
    Player fire at the target.
    Author: ChuyangLiu
    */
    virtual void fire(cocos2d::Layer *layer, const cocos2d::Vec2 *target = nullptr) override;

protected:

private:
    /*
    Inaccessible default constructor from outside the class.
    Use create() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    PlayerSingleSprite();

    /*
    Implement onRemove event
    Author: ChuyangLiu
    */
    virtual void onRemove() override;
};
