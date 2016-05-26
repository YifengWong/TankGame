#pragma once

// Forward declaration
class cocos2d::Vec2;
class cocos2d::Size;

/*
Utilities for layout operation.
*/
class LayoutUtil {
public:
    /*
    Return origin position of the game window.
    Author: ChuyangLiu
    */
    static cocos2d::Vec2 getOrigin();

    /*
    Return visible size of the game window.
    Author: ChuyangLiu
    */
    static cocos2d::Size getVisibleSize();

    /*
    Return center position of the game window.
    Author: ChuyangLiu
    */
    static cocos2d::Vec2 getCenterPosition();
};
