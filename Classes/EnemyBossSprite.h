#pragma once

#include "EnemySpriteBase.h"

class GameScene1Player;

/*
A boss sprite
*/
class EnemyBossSprite : public EnemySpriteBase {
public:
    virtual ~EnemyBossSprite();

	/*
	Create an enemy sprite.
	Author: YifengWong & ChuyangLiu
	*/
	static EnemyBossSprite* create(GameScene1Player *scene);

private:
	/*
	Inaccessible default constructor from outside the class.
	Use create() to create the instance from outside the class.
	Author: YifengWong
	*/
    EnemyBossSprite();

    /*
    Enemy fire at the target.
    Author: YifengWong
    */
    virtual void fire(const cocos2d::Vec2 &target) override;

    /*
    Make an AI decision.
    Author: YifengWong & ChuyangLiu
    */
    virtual void makeAIDecision() override;
};
