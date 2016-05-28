#include "EnemyBulletSprite.h"
#include "GameParam.h"

USING_NS_CC;

EnemyBulletSprite* EnemyBulletSprite::create() {
    EnemyBulletSprite *bullet = new (std::nothrow) EnemyBulletSprite();
    if (bullet && bullet->initWithFile("bullet_enemy.png")) {
        bullet->autorelease();

        // Create physics body
        auto physicBody = PhysicsBody::createCircle(bullet->getContentSize().height / 2);
        // Set group and bitmasks
        physicBody->setGroup(GameParam::BULLET_ENEMY_PHYSIC_GROUP);
        physicBody->setCategoryBitmask(GameParam::BULLET_ENEMY_PHYSIC_CATEGORY_BM);
        physicBody->setCollisionBitmask(GameParam::BULLET_ENEMY_PHYSIC_COLLISION_BM);
        physicBody->setContactTestBitmask(GameParam::BULLET_ENEMY_PHYSIC_CONTACT_BM);
        physicBody->setTag(GameParam::BULLET_ENEMY_TAG);

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
        if (this) {
            this->removeFromParent();
        }
    }, GameParam::BULLET_LAST_TIME, "BulletSchedule");
}
