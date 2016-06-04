#pragma once

#include "SpriteBase.h"

class BulletSpriteBase : public SpriteBase {
public:
    BulletSpriteBase();
    virtual ~BulletSpriteBase();

protected:
    /*
    Create a schedule to remove the bullet after some time.
    Author: ChuyangLiu
    */
    void scheduleAutoRemove();

private:

};
