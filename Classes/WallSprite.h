#pragma once

/*
A wall sprite
*/
class WallSprite : public cocos2d::Sprite {
public:
    ~WallSprite();

    /*
    Create a wall sprite.
    Author: ChuyangLiu
    */
    static WallSprite* create(const bool &breakable);

    /*
    Set the breakable field.
    Author: ChuyangLiu
    */
    void setBreakable(const bool &b);

    /*
    Return the breakable field.
    Author: ChuyangLiu
    */
    bool isBreakable() const;

private:
    bool breakable;

    /*
    Inaccessible default constructor from outside the class.
    Use create() to create the instance from outside the class.
    Author: ChuyangLiu
    */
    WallSprite();
};
