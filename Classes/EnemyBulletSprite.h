#pragma once

/*
An enemy bullet sprite
*/
class EnemyBulletSprite : public cocos2d::Sprite {
public:
    /*
    Create a bullet for enemy.
    Author: ChuyangLiu
    */
    static EnemyBulletSprite* createEnemyBullet();

private:
    /*
    Create a schedule to disappear the bullet after some time.
    Author: ChuyangLiu
    */
    void scheduleAutoDisappear();

;};
