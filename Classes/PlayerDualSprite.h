#pragma once

#include "PlayerSpriteBase.h"

/*
A player sprite for dual model
*/
class PlayerDualSprite : public PlayerSpriteBase {
public:
    virtual ~PlayerDualSprite();

    /*
    Define the VS players type to help creating.
    Author: YifengWong
    */
    enum VSPlayerType {
        PLAYER_1,
        PLAYER_2
    };

	/*
	Create a player sprite with players type.
	Author: YifengWong
	*/
	static PlayerDualSprite* create(PlayerDualSprite::VSPlayerType type);

	/*
	Set the move value of the player towards the direction, and change the picture.
	Author: YifengWong
	*/
    virtual void setMoveVal(const Direction &direc) override;

	/*
	Reset the move value of the player towards the direction.
	Author: YifengWong
	*/
    virtual void resetMoveVal(const Direction &direc) override;

	/*
	Player fire at the target.
	Author: YifengWong
	*/
    virtual void fire(cocos2d::Layer *layer, const cocos2d::Vec2 *target = nullptr) override;

private:
	Direction dir;
    PlayerDualSprite::VSPlayerType type;

	/*
	Inaccessible default constructor from outside the class.
	Use create() to create the instance from outside the class.
	Author: YifengWong
	*/
    PlayerDualSprite();
};
