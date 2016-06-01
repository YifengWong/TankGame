#include "PlayerBulletSprite.h"
#include "GameConfig.h"

USING_NS_CC;

unsigned PlayerBulletSprite::bulletCnt = 0;

PlayerBulletSprite* PlayerBulletSprite::create() {
    PlayerBulletSprite *bullet = new (std::nothrow) PlayerBulletSprite();
    if (bullet && bullet->initWithFile("bullet_player.png")) {
        bullet->autorelease();

        // Create physics body
        auto physicBody = PhysicsBody::createCircle(bullet->getContentSize().height / 2);
        // Set group and bitmasks
        physicBody->setGroup(GameConfig::BULLET_PLAYER_PHYSIC_GROUP);
        physicBody->setCategoryBitmask(GameConfig::BULLET_PLAYER_PHYSIC_CATEGORY_BM);
        physicBody->setCollisionBitmask(GameConfig::BULLET_PLAYER_PHYSIC_COLLISION_BM);
        physicBody->setContactTestBitmask(GameConfig::BULLET_PLAYER_PHYSIC_CONTACT_BM);
        physicBody->setTag(GameConfig::BULLET_PLAYER_TAG);

        // Set bullet sprites
        bullet->setAnchorPoint(Vec2(0.5, 0.5));
        bullet->setPhysicsBody(physicBody);
        bullet->scheduleAutoDisappear();
        ++PlayerBulletSprite::bulletCnt;

        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}

void PlayerBulletSprite::onRemove() {
    if (bulletCnt > 0) {
        --bulletCnt;
    }
}

unsigned PlayerBulletSprite::getBulletCount() {
    return bulletCnt;
}
