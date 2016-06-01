#pragma once

#include "HPValue.h"

class AliveSpriteBase : public cocos2d::Sprite{
public:
    /*
    Check if the sprite is dead.
    Author: ChuyangLiu
    */
    bool isDead();

    /*
    Return the hp value.
    Author: ChuyangLiu
    */
    HPValue* getHP();

    /*
    Set the hp value.
    Author: ChuyangLiu
    */
    void setHP(const HPValue &hp_);

private:
    HPValue hp;
};
