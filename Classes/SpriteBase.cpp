#include "SpriteBase.h"
#include "GameScene1Player.h"

SpriteBase::SpriteBase() {
}

SpriteBase::~SpriteBase() {
}

void SpriteBase::removeFromParent() {
    // Use mutual exclusive lock to enable thread-safe
    mutex.lock();
    if (removed) {
        mutex.unlock();
        return;
    } else {
        removed = true;
        mutex.unlock();
    }

    onRemove();  // Trigger onRemove() event
    Sprite::removeFromParent();
}

void SpriteBase::onRemove() {
    // Not implemented
}

void SpriteBase::setGameScene(GameScene1Player *gameScene_) {
    gameScene = gameScene_;
}

GameScene1Player* SpriteBase::getGameScene() {
    return gameScene;
}
