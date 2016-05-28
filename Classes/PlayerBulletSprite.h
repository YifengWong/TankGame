#pragma once

/*
A player bullet sprite
*/
class PlayerBulletSprite : public cocos2d::Sprite {
public:
    /*
    Create a bullet for player.
    Author: ChuyangLiu
    */
    static PlayerBulletSprite* create();

    /*
    Remove the sprite from the parent
    Override Node::removeFromParent()
    Author: ChuyangLiu
    */
    void removeFromParent();

    /*
    Return the bullet count.
    Author: ChuyangLiu
    */
    static unsigned getBulletCount();

private:
    static unsigned bulletCnt;

    /*
    Create a schedule to disappear the bullet after some time.
    Author: ChuyangLiu
    */
    void scheduleAutoDisappear();

;};
