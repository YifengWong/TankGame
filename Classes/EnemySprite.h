#pragma once

#include "PlayerSprite.h"

/*
An enemey sprite
*/
class EnemySprite : public cocos2d::Sprite {
public:
    /*
    Create an enemy sprite.
    Author: ChuyangLiu
    */
    static EnemySprite* create(cocos2d::Layer *layer, PlayerSprite* player);

private:
    cocos2d::Layer *layer = NULL;
    PlayerSprite *player = NULL;

    /*
    Set the layer of the enemy.
    Author: ChuyangLiu
    */
    void setLayer(cocos2d::Layer *layer_);

    /*
    Set the player of the game.
    Author: ChuyangLiu
    */
    void setPlayer(PlayerSprite *player_);

    /*
    Schedule the enemy AI.
    Author: ChuyangLiu
    */
    void scheduleAI();

    /*
    Enemy fire at the target.
    Author: ChuyangLiu
    */
    void fire(const cocos2d::Vec2 &target);
};
