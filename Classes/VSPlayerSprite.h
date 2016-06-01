#pragma once

#include "HPValue.h"
#include "GameUtil.h"

/*
A player sprite for VS
*/
class VSPlayerSprite : public cocos2d::Sprite {
public:
	/*
	Create a player sprite with players type.
	Author: YifengWong
	*/
	static VSPlayerSprite* create(GameUtil::VSPlayerType type);

	/*
	Set the move value of the player towards the direction, and change the picture.
	Author: YifengWong
	*/
	void setMoveVal(const Direction &direc);

	/*
	Reset the move value of the player towards the direction.
	Author: YifengWong
	*/
	void resetMoveVal(const Direction &direc);

	/*
	Player fire at the target.
	Author: YifengWong
	*/
	void fire(cocos2d::Layer *layer);

	/*
	Check if the player is dead.
	Author: YifengWong
	*/
	bool isDead();

	/*
	Return the hp value.
	Author: YifengWong
	*/
	HPValue* getHP();

private:
	HPValue hp;
	Direction dir;
	GameUtil::VSPlayerType type;

	/*
	Inaccessible default constructor from outside the class.
	Use create() to create the instance from outside the class.
	Author: YifengWong
	*/
	VSPlayerSprite() {}
};
