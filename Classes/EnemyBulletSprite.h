#pragma once

#include "BulletSpriteBase.h"

/*
An enemy bullet sprite
*/
class EnemyBulletSprite : public BulletSpriteBase {
public:
    /*
    Create a bullet for enemy.
    Author: ChuyangLiu
    */
    static EnemyBulletSprite* create();

private:
    /*
    Inaccessible default constructor from outside the class.
    Use create() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    EnemyBulletSprite() {}

    /*
    onRemove() event called in removeFromParent()
    Author: ChuyangLiu
    */
    virtual void onRemove();

;};
