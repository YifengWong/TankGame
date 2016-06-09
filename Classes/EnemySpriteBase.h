#pragma once

#include "AliveSpriteBase.h"
#include "SpriteBase.h"

/*
Base class for an enemy sprite
*/
class EnemySpriteBase : public AliveSpriteBase, public SpriteBase {
public:
    EnemySpriteBase();
    virtual ~EnemySpriteBase();

    /*
    Enemy fire at the target.
    Author: ChuyangLiu
    */
    virtual void fire(const cocos2d::Vec2 &target) = 0;

    /*
    Make an AI decision.
    Author: ChuyangLiu
    */
    virtual void makeAIDecision() = 0;

    /*
    Implement onRemove event
    Author: ChuyangLiu
    */
    virtual void onRemove() override;


protected:

    /*
    Run the enemy AI.
    Author: ChuyangLiu
    */
    void runAI();

	/*
	Update the hp bar
	Author: YifengWong
	*/
	void updateHpBar();

	/*
	Show the hp bar
	Author: YifengWong
	*/
	void showHpBar();

	/*
	Set the hp bar
	Author: YifengWong
	*/
	void setHpBar();

	/*
	Remove the hp bar
	Author: YifengWong
	*/
	void removeHpBar();

	cocos2d::ProgressTimer* hpSprite;

private:
};
