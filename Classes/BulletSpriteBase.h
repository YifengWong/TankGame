#pragma once

class BulletSpriteBase : public cocos2d::Sprite {
public:
    /*
    Remove the sprite from the parent
    Override Node::removeFromParent()
    This is a thread-safe method.
    Author: ChuyangLiu
    */
    void removeFromParent();

protected:
    /*
    Create a schedule to remove the bullet after some time.
    Author: ChuyangLiu
    */
    void scheduleAutoRemove();

    /*
    onRemove() event called in removeFromParent()
    Author: ChuyangLiu
    */
    virtual void onRemove() = 0;

private:
    bool removed = false;

    std::mutex mutex;
};
