#pragma once

#include "EnemySpriteBase.h"

/*
A boss sprite
*/
class EnemyBossSprite : public EnemySpriteBase {
public:
	/*
	Create an enemy sprite.
	Author: YifengWong & ChuyangLiu
	*/
	static EnemyBossSprite* create(cocos2d::Layer *layer = nullptr);

private:
	/*
	Inaccessible default constructor from outside the class.
	Use create() to create the instance from outside the class.
	Author: YifengWong
	*/
	EnemyBossSprite() {}

    /*
    Enemy fire at the target.
    Author: YifengWong
    */
    virtual void fire(const cocos2d::Vec2 &target);

    /*
    Make an AI decision.
    Author: YifengWong & ChuyangLiu
    */
    virtual void makeAIDecision();
};
