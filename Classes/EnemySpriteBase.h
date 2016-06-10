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

protected:
    /*
    Run the enemy AI.
    Author: ChuyangLiu
    */
    void runAI();

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

private:
    /*
    Update the hp bar at every frame
    Author: YifengWong & ChuyangLiu
    */
    virtual void updateHpBar() override;
};
