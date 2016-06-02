#pragma once

#include "HPValue.h"

class AliveSpriteBase : public cocos2d::Sprite{
public:
    /*
    Check if the sprite is dead.
    Author: ChuyangLiu
    */
    bool isDead() const;

    /*
    Return the hp value.
    Author: ChuyangLiu
    */
    const HPValue* getHP() const;

    /*
    Set the hp value.
    Author: ChuyangLiu
    */
    void setHP(const HPValue &hp_);

    /*
    Increase the hp value.
    Author: ChuyangLiu
    */
    void increaseHP(const int v);

    /*
    Decrease the hp value.
    Author: ChuyangLiu
    */
    void decreaseHP(const int v);

private:
    HPValue hp;
};
