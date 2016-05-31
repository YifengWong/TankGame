#pragma once

#include "PlayerSprite.h"

/*
An enemey sprite
*/
class BossSprite : public cocos2d::Sprite {
public:
	/*
	Create an enemy sprite.
	Author: YifengWong
	*/
	static BossSprite* create(cocos2d::Layer *layer = nullptr);

private:
	cocos2d::Layer *layer = nullptr;

	/*
	Inaccessible default constructor from outside the class.
	Use create() to create the instance from outside the class.
	Author: YifengWong
	*/
	BossSprite() {}

	/*
	Set the layer of the enemy.
	Author: YifengWong
	*/
	void setLayer(cocos2d::Layer *layer_);

	/*
	Schedule the enemy AI to fire.
	Author: YifengWong
	*/
	void scheduleAI();

	/*
	Enemy fire at the target.
	Author: YifengWong
	*/
	void fire(const cocos2d::Vec2 &target);
};
