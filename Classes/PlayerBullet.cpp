#include "PlayerBullet.h"
#include "Constants.h"

USING_NS_CC;

PlayerBullet* PlayerBullet::create() {
    auto sprite = Sprite::create("bullet_player_test.png");
    auto bullet = static_cast<PlayerBullet*>(sprite);

    // Create physics body
    auto physicBody = PhysicsBody::createCircle(bullet->getContentSize().height / 2);
    // Set group and bitmasks
    physicBody->setGroup(Constants::PLAYER_BULLET_PHYSIC_GROUP);
    physicBody->setCategoryBitmask(Constants::PLAYER_BULLET_PHYSIC_CATEGORY_BM);
    physicBody->setCollisionBitmask(Constants::PLAYER_BULLET_PHYSIC_COLLISION_BM);
    physicBody->setContactTestBitmask(Constants::PLAYER_BULLET_PHYSIC_CONTACT_BM);

    // Set player sprites
    bullet->setAnchorPoint(Vec2(0.5, 0.5));
    bullet->setPhysicsBody(physicBody);
    bullet->scheduleAutoDisappear();

    return bullet;
}

void PlayerBullet::scheduleAutoDisappear() {
    scheduleOnce([&](float f) {
        this->removeFromParent();
    }, Constants::BULLET_LAST_TIME, "key");
}
