#pragma once

/*
Player's bullet.
*/
class PlayerBullet : public cocos2d::Sprite {
public:
    /*
    Create a player bullet.
    Author: ChuyangLiu
    */
    static PlayerBullet* create();

private:
    /*
    Create a schedule to disappear the bullet after some time.
    Author: ChuyangLiu
    */
    void scheduleAutoDisappear();
;};
