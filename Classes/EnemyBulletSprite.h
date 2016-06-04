#pragma once

#include "BulletSpriteBase.h"

/*
An enemy bullet sprite
*/
class EnemyBulletSprite : public BulletSpriteBase {
public:
    virtual ~EnemyBulletSprite();

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
    EnemyBulletSprite();
;};
