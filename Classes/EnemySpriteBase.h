#pragma once

#include "AliveSpriteBase.h"

class GameScene1Player;

/*
Base class for an enemy sprite
*/
class EnemySpriteBase : public AliveSpriteBase {
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

protected:
    /*
    Set the layer of the enemy.
    Author: ChuyangLiu
    */
    void setGameScene(GameScene1Player *gameScene_);

    /*
    Return the layer of the enemy.
    Author: ChuyangLiu
    */
    GameScene1Player* getGameScene();

    /*
    Run the enemy AI.
    Author: ChuyangLiu
    */
    void runAI();

private:
    // The GameScene layer of the enemy
    GameScene1Player *gameScene = nullptr;
};
