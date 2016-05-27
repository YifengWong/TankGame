#include "EnemyBulletSprite.h"
#include "Constants.h"

USING_NS_CC;

EnemyBulletSprite* EnemyBulletSprite::createEnemyBullet() {
    auto sprite = Sprite::create("bullet_enemy.png");
    auto bullet = static_cast<EnemyBulletSprite*>(sprite);

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

void EnemyBulletSprite::scheduleAutoDisappear() {
    // The third param is not used
    scheduleOnce([&](float f) {
        this->removeFromParent();
    }, Constants::BULLET_LAST_TIME, "BulletSchedule");
}
