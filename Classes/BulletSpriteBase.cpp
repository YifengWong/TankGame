#include "BulletSpriteBase.h"
#include "GameConfig.h"

void BulletSpriteBase::scheduleAutoDisappear() {
    // The third param is not used
    scheduleOnce([&](float f) {
        if (this) {
            this->removeFromParent();
        }
    }, GameConfig::BULLET_LAST_TIME, "BulletSchedule");
}

void BulletSpriteBase::removeFromParent() {
    mutex.lock();
    if (removed) {
        mutex.unlock();
        return;
    } else {
        removed = true;
        mutex.unlock();
    }

    onRemove();  // Call onRemove() cb
    Sprite::removeFromParent();
}

