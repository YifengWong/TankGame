#include "EnemyBulletSprite.h"
#include "Constants.h"

USING_NS_CC;

EnemyBulletSprite* EnemyBulletSprite::create() {
    EnemyBulletSprite *bullet = new (std::nothrow) EnemyBulletSprite();
    if (bullet && bullet->initWithFile("bullet_enemy.png")) {
        bullet->autorelease();

        // Create physics body
        auto physicBody = PhysicsBody::createCircle(bullet->getContentSize().height / 2);
        // Set group and bitmasks
        physicBody->setGroup(Constants::BULLET_ENEMY_PHYSIC_GROUP);
        physicBody->setCategoryBitmask(Constants::BULLET_ENEMY_PHYSIC_CATEGORY_BM);
        physicBody->setCollisionBitmask(Constants::BULLET_ENEMY_PHYSIC_COLLISION_BM);
        physicBody->setContactTestBitmask(Constants::BULLET_ENEMY_PHYSIC_CONTACT_BM);
        physicBody->setTag(Constants::BULLET_ENEMY_TAG);

        // Set bullet sprites
        bullet->setAnchorPoint(Vec2(0.5, 0.5));
        bullet->setPhysicsBody(physicBody);
        bullet->scheduleAutoDisappear();

        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}

void EnemyBulletSprite::scheduleAutoDisappear() {
    // The third param is not used
    scheduleOnce([&](float f) {
        if (this != nullptr) {
            this->removeFromParent();
        }
    }, Constants::BULLET_LAST_TIME, "BulletSchedule");
}
