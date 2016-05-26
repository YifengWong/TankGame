#pragma once

/*
Player sprite: a subclass of cocos2d::sprite
*/
class PlayerSprite : public cocos2d::Sprite {
public:
    /*
    Create a player sprite.
    Author: ChuyangLiu
    */
    static PlayerSprite* create();

    /*
    Move direction declaration.
    Author: ChuyangLiu
    */
    enum Direction { LEFT, UP, RIGHT, DOWN };

    /*
    Move the player towards the direction
    Author: ChuyangLiu
    */
    void startMove(const Direction &direc);

    /*
    Stop moving the towards the direction
    Author: ChuyangLiu
    */
    void stopMove(const Direction &direc);

private:

};
