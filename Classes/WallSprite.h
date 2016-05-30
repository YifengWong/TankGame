#pragma once

/*
A wall sprite
*/
class WallSprite : public cocos2d::Sprite {
public:
    /*
    Create a wall sprite.
    Author: ChuyangLiu
    */
    static WallSprite* create();

private:
    /*
    Inaccessible default constructor from outside the class.
    Use create() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    WallSprite() {}
};
