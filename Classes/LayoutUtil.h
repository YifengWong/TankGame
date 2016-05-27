#pragma once

/*
Move direction declaration.
Author: ChuyangLiu
*/
enum Direction { LEFT, UP, RIGHT, DOWN };

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

    /*
    Check if a sprite reaches the {LEFT|UP|RIGHT|DOWN} boundary 
    Author: ChuyangLiu
    */
    static bool isReachBoundary(const cocos2d::Sprite *sprite, const Direction &boundDirec);
};
