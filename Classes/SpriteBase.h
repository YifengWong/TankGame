#pragma once


class GameScene1Player;

class SpriteBase : public cocos2d::Sprite {
public:
    SpriteBase();
    virtual ~SpriteBase();

    /*
    Remove the sprite from the parent
    Use this method instead of Sprite::removeFromParent()
    This is a thread-safe method.
    Author: ChuyangLiu
    */
    virtual void removeFromParent() final;

protected:
    /*
    onRemove() event called in removeFromParent()
    Author: ChuyangLiu
    */
    virtual void onRemove();

    /*
    Set the game scene of the sprite.
    Author: ChuyangLiu
    */
    void setGameScene(GameScene1Player *gameScene_);

    /*
    Return the game scene of the sprite.
    Author: ChuyangLiu
    */
    GameScene1Player* getGameScene();


private:
    std::mutex mutex;
    bool removed = false;

    GameScene1Player *gameScene = nullptr;
};
