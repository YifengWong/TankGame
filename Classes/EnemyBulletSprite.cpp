#include "EnemyBulletSprite.h"
#include "GameConfig.h"

USING_NS_CC;

EnemyBulletSprite* EnemyBulletSprite::create() {
    EnemyBulletSprite *bullet = new (std::nothrow) EnemyBulletSprite();
    if (bullet && bullet->initWithFile("bullet_enemy.png")) {
        bullet->autorelease();

        // Create physics body
        auto physicBody = PhysicsBody::createCircle(bullet->getContentSize().height / 2);
        // Set group and bitmasks
        physicBody->setGroup(GameConfig::BULLET_ENEMY_PHYSIC_GROUP);
        physicBody->setCategoryBitmask(GameConfig::BULLET_ENEMY_PHYSIC_CATEGORY_BM);
        physicBody->setCollisionBitmask(GameConfig::BULLET_ENEMY_PHYSIC_COLLISION_BM);
        physicBody->setContactTestBitmask(GameConfig::BULLET_ENEMY_PHYSIC_CONTACT_BM);
        physicBody->setTag(GameConfig::BULLET_ENEMY_TAG);

        // Set bullet sprites
        bullet->setAnchorPoint(Vec2(0.5, 0.5));
        bullet->setPhysicsBody(physicBody);
        bullet->scheduleAutoDisappear();

        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}

void EnemyBulletSprite::onRemove() {
    // Do nothing
}