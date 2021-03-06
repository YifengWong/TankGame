#pragma once

#include <string>

class EnemySpriteBase;

/*
Game utilities
*/
class GameUtil {
public:
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
        CORNER_LEFT_BOTTOM,
        EDGE_CENTER_LEFT,
        EDGE_CENTER_TOP,
        EDGE_CENTER_RIGHT,
        EDGE_CENTER_BOTTOM
    };

    /*
    Return one predefined position specified by @param type
    Author: ChuyangLiu
    */
    static cocos2d::Vec2 getPosition(const PositionType &type);
    static int getPositionTypeCount();

    /*
    Return one position at @param row and @param column of the window
    Author: ChuyangLiu
    */
    static cocos2d::Vec2 getPosition(const int &row, const int &column);

    /*
    Preload game music.
    Author: ChuyangLiu
    */
    static void preloadMusic();

    /*
    Play effect music 
    @param effectType the effect music type
    Author: ChuyangLiu
    */
    enum MusicEffectType {
        BULLET_HIT
    };
    static void playEffect(const MusicEffectType &effectType);

    /*
    Play background music
    @param bgType the background music type
    Author: ChuyangLiu
    */
    enum MusicBgType {
        HOME_PAGE
    };
    static void playBgMusic(const MusicBgType &bgType);

    /*
    Add particle effect
    Author: ChuyangLiu
    */
    enum ParticleType {
        EXPLODE
    };
    static void addParticles(cocos2d::Layer *layer, const cocos2d::Vec2 &pos, const ParticleType &type);

    /*
    Convert a int value to string
    Author: ChuyangLiu
    */
    static std::string convertToString(const int &v);

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

    /*
    Change current scene to home scene
    Author: ChuyangLiu
    */
    static void toHomeScene();

    /*
    Change current scene to GameScene1Player scene
    Author: ChuyangLiu
    */
    static void toGameScene1Player();

    /*
    Change scene to next checkpoint
    Author: ChuyangLiu
    */
    static void toNextCheckpoint();

    /*
    Check if current checkpoint is the last checkpoint
    Author: ChuyangLiu
    */
    static bool hasNextCheckpoint();

private:
    /*
    Reset some fields before replace to a new scene
    Author: ChuyangLiu
    */
    static void resetBeforeReplace();
};
