#include "BulletSpriteBase.h"
#include "GameConfig.h"

BulletSpriteBase::BulletSpriteBase() {
}

BulletSpriteBase::~BulletSpriteBase() {
}

void BulletSpriteBase::scheduleAutoRemove() {
    // The third param is not used
    scheduleOnce([&](float f) {
        if (this) {
            this->removeFromParent();
        }
    }, GameConfig::BULLET_LAST_TIME, "BulletSchedule");
}
