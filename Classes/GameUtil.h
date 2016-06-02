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
Game utilities
*/
class GameUtil {
public:
    /*
    Return to home scene.
    Author: ChuyangLiu
    */
    static void returnToHome();

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
    Return one position specified by @param type
    position of the game window.
    Author: ChuyangLiu
    */
    static cocos2d::Vec2 getPosition(const PositionType &type);
    static int getPositionTypeCount();

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
