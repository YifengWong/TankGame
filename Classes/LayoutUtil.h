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
    Return {CENTER|LEFT_TOP|LEFT_BOTTOM|RIGHT_TOP|RIGHT_BOTTOM} 
    position of the game window.
    Author: ChuyangLiu
    */
    enum PositionType { CENTER, LEFT_TOP, LEFT_BOTTOM, RIGHT_TOP, RIGHT_BOTTOM };
    static cocos2d::Vec2 getPosition(const PositionType &type);

    /*
    Check if a sprite reaches the {LEFT|UP|RIGHT|DOWN} boundary 
    Author: ChuyangLiu
    */
    static bool isReachBoundary(const cocos2d::Sprite *sprite, const Direction &boundDirec);
};
