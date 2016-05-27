#pragma once

/*
A bullet sprite
*/
class BulletSprite : public cocos2d::Sprite {
public:
    /*
    Create a bullet for player.
    Author: ChuyangLiu
    */
    static BulletSprite* createPlayerBullet();

    /*
    Create a bullet for enemy.
    Author: ChuyangLiu
    */
    static BulletSprite* createEnemyBullet();

private:
    /*
    Create a schedule to disappear the bullet after some time.
    Author: ChuyangLiu
    */
    void scheduleAutoDisappear();

;};
