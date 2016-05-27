#include "PlayerBulletSprite.h"
#include "Constants.h"

USING_NS_CC;

PlayerBulletSprite* PlayerBulletSprite::createPlayerBullet() {
    auto sprite = Sprite::create("bullet_player.png");
    auto bullet = static_cast<PlayerBulletSprite*>(sprite);

    // Create physics body
    auto physicBody = PhysicsBody::createCircle(bullet->getContentSize().height / 2);
    // Set group and bitmasks
    physicBody->setGroup(Constants::BULLET_PLAYER_PHYSIC_GROUP);
    physicBody->setCategoryBitmask(Constants::BULLET_PLAYER_PHYSIC_CATEGORY_BM);
    physicBody->setCollisionBitmask(Constants::BULLET_PLAYER_PHYSIC_COLLISION_BM);
    physicBody->setContactTestBitmask(Constants::BULLET_PLAYER_PHYSIC_CONTACT_BM);
    physicBody->setTag(Constants::BULLET_PLAYER_TAG);

    // Set bullet sprites
    bullet->setAnchorPoint(Vec2(0.5, 0.5));
    bullet->setPhysicsBody(physicBody);
    bullet->scheduleAutoDisappear();

    return bullet;
}

void PlayerBulletSprite::scheduleAutoDisappear() {
    // The third param is not used
    scheduleOnce([&](float f) {
        this->removeFromParent();
    }, Constants::BULLET_LAST_TIME, "BulletSchedule");
}
