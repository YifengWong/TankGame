#pragma once

class EnemySpriteBase;

/*
Move direction declaration.
Author: ChuyangLiu
*/
enum Direction {
    LEFT,
    UP,
    RIGHT,
    DOWN
};

/*
Utilities for layout operation.
*/
class GameUtil {
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
    Get the unit direction vector between two points.
    Author: ChuyangLiu
    */
    static cocos2d::Vec2 getUnitDirectionVector(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to);

    /*
    Check if a sprite reaches the {LEFT|UP|RIGHT|DOWN} boundary 
    Author: ChuyangLiu
    */
    static bool isReachBoundary(const cocos2d::Sprite *sprite, const Direction &boundDirec);

    /*
    Predefined PositionType declaration.
    Author: ChuyangLiu
    */
    enum PositionType {
        LEFT_TOP,
        LEFT_BOTTOM,
        RIGHT_TOP,
        RIGHT_BOTTOM,
        CENTER,
        CENTER_LEFT,
        CENTER_TOP,
        CENTER_RIGHT,
        CENTER_DOWN,
        CORNER_LEFT_TOP,
        CORNER_RIGHT_TOP,
        CORNER_RIGHT_BOTTOM,
        CORNER_LEFT_BOTTOM
    };

    /*
    Return one position specified by @param type
    position of the game window.
    Author: ChuyangLiu
    */
    static cocos2d::Vec2 getPosition(const PositionType &type);

    /*
    Check if the enemy is a normal enemy
    Author: ChuyangLiu
    */
    static bool isNormalEnemy(EnemySpriteBase *enemy);

    /*
    Check if the enemy is a boss enemy
    Author: ChuyangLiu
    */
    static bool isBossEnemy(EnemySpriteBase *enemy);
};
