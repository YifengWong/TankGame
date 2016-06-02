#pragma once

#include "BulletSpriteBase.h"

/*
A player bullet sprite
*/
class PlayerBulletSprite : public BulletSpriteBase {
public:
    /*
    Create a bullet for player.
    Author: ChuyangLiu
    */
    static PlayerBulletSprite* create();

    /*
    Return the bullet count.
    Author: ChuyangLiu
    */
    static unsigned getBulletCount();

    /*
    Set the bullet count to zero.
    Author: ChuyangLiu
    */
    static void clearBulletCount();

private:
    static unsigned bulletCnt;

    /*
    Inaccessible default constructor from outside the class.
    Use create() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    PlayerBulletSprite() {}

    /*
    onRemove() event called in removeFromParent()
    Author: ChuyangLiu
    */
    virtual void onRemove() override;
;};
