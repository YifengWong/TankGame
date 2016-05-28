#include "PlayerSprite.h"
#include "Constants.h"
#include "PlayerBulletSprite.h"

USING_NS_CC;

PlayerSprite* PlayerSprite::create() {
    auto sprite = Sprite::create("player.png");
    auto player = static_cast<PlayerSprite*>(sprite);

    // Create physics body
    auto physicBody = PhysicsBody::createBox(player->getContentSize());
    // Set group and bitmasks
    physicBody->setGroup(Constants::PLAYER_PHYSIC_GROUP);
    physicBody->setCategoryBitmask(Constants::PLAYER_PHYSIC_CATEGORY_BM);
    physicBody->setCollisionBitmask(Constants::PLAYER_PHYSIC_COLLISION_BM);
    physicBody->setContactTestBitmask(Constants::PLAYER_PHYSIC_CONTACT_BM);
    physicBody->setRotationEnable(false);
    physicBody->setTag(Constants::PLAYER_TAG);

    // Set player sprites
    player->setAnchorPoint(Vec2(0.5, 0.5));
    player->setPhysicsBody(physicBody);
    //player->moveX = player->moveY = 0;

    return player;
}

void PlayerSprite::setMoveVal(const Direction &direc) {
    auto physicBody = getPhysicsBody();
    if (physicBody == NULL) return;
    switch (direc) {
        case LEFT:
            physicBody->setVelocity(Vec2(-Constants::PLAYER_MOVE_UNIT, physicBody->getVelocity().y));
            break;
        case UP:
            physicBody->setVelocity(Vec2(physicBody->getVelocity().x, Constants::PLAYER_MOVE_UNIT));
            break;
        case RIGHT:
            physicBody->setVelocity(Vec2(Constants::PLAYER_MOVE_UNIT, physicBody->getVelocity().y));
            break;
        case DOWN:
            physicBody->setVelocity(Vec2(physicBody->getVelocity().x, -Constants::PLAYER_MOVE_UNIT));
            break;
        default:
            break;
    }
}

void PlayerSprite::resetMoveVal(const Direction &direc) {
    auto physicBody = getPhysicsBody();
    if (physicBody == NULL) return;
    switch (direc) {
        case LEFT:
            if (physicBody->getVelocity().x == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(Constants::PLAYER_MOVE_UNIT, 0));
            break;
        case UP:
            if (physicBody->getVelocity().y == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(0, -Constants::PLAYER_MOVE_UNIT));
            break;
        case RIGHT:
            if (physicBody->getVelocity().x == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(-Constants::PLAYER_MOVE_UNIT, 0));
            break;
        case DOWN:
            if (physicBody->getVelocity().y == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(0, Constants::PLAYER_MOVE_UNIT));
            break;
        default:
            break;
    }
}

void PlayerSprite::fire(Layer *layer, const cocos2d::Vec2 &target) {
    auto vec = LayoutUtil::getUnitDirectionVector(getPosition(), target);
    // Add bullet
    auto bullet = PlayerBulletSprite::createPlayerBullet();
    bullet->setPosition(getPosition());
    bullet->getPhysicsBody()->setVelocity(vec * Constants::PLAYER_BULLET_SPEED);
    // Add to layer
    layer->addChild(bullet);
}
