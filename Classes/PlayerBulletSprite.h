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

private:
    /*
    Create a schedule to disappear the bullet after some time.
    Author: ChuyangLiu
    */
    void scheduleAutoDisappear();

;};
