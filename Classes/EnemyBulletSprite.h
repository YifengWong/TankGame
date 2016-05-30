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
    static EnemyBulletSprite* create();

private:

    /*
    Inaccessible default constructor from outside the class.
    Use create() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    EnemyBulletSprite() {}

    /*
    Create a schedule to disappear the bullet after some time.
    Author: ChuyangLiu
    */
    void scheduleAutoDisappear();

;};
