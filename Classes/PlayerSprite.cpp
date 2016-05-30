#include "PlayerSprite.h"
#include "GameConfig.h"
#include "PlayerBulletSprite.h"

USING_NS_CC;

PlayerSprite* PlayerSprite::create() {
    PlayerSprite *player = new (std::nothrow) PlayerSprite();
    if (player && player->initWithFile("player.png")) {
        player->autorelease();

        // Create physics body
        auto physicBody = PhysicsBody::createBox(player->getContentSize());
        // Set group and bitmasks
        physicBody->setGroup(GameConfig::PLAYER_PHYSIC_GROUP);
        physicBody->setCategoryBitmask(GameConfig::PLAYER_PHYSIC_CATEGORY_BM);
        physicBody->setCollisionBitmask(GameConfig::PLAYER_PHYSIC_COLLISION_BM);
        physicBody->setContactTestBitmask(GameConfig::PLAYER_PHYSIC_CONTACT_BM);
        physicBody->setRotationEnable(false);
        physicBody->setTag(GameConfig::PLAYER_TAG);

        // Set player sprites
        player->setAnchorPoint(Vec2(0.5, 0.5));
        player->setPhysicsBody(physicBody);

        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

void PlayerSprite::setMoveVal(const Direction &direc) {
    auto physicBody = getPhysicsBody();
    if (physicBody == nullptr) return;
    switch (direc) {
        case LEFT:
            physicBody->setVelocity(Vec2(-GameConfig::PLAYER_MOVE_UNIT, physicBody->getVelocity().y));
            break;
        case UP:
            physicBody->setVelocity(Vec2(physicBody->getVelocity().x, GameConfig::PLAYER_MOVE_UNIT));
            break;
        case RIGHT:
            physicBody->setVelocity(Vec2(GameConfig::PLAYER_MOVE_UNIT, physicBody->getVelocity().y));
            break;
        case DOWN:
            physicBody->setVelocity(Vec2(physicBody->getVelocity().x, -GameConfig::PLAYER_MOVE_UNIT));
            break;
        default:
            break;
    }
}

void PlayerSprite::resetMoveVal(const Direction &direc) {
    auto physicBody = getPhysicsBody();
    if (physicBody == nullptr) return;
    switch (direc) {
        case LEFT:
            if (physicBody->getVelocity().x == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(GameConfig::PLAYER_MOVE_UNIT, 0));
            break;
        case UP:
            if (physicBody->getVelocity().y == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(0, -GameConfig::PLAYER_MOVE_UNIT));
            break;
        case RIGHT:
            if (physicBody->getVelocity().x == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(-GameConfig::PLAYER_MOVE_UNIT, 0));
            break;
        case DOWN:
            if (physicBody->getVelocity().y == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(0, GameConfig::PLAYER_MOVE_UNIT));
            break;
        default:
            break;
    }
}

void PlayerSprite::fire(Layer *layer, const cocos2d::Vec2 &target) {
    auto vec = LayoutUtil::getUnitDirectionVector(getPosition(), target);
    // Add bullet
    auto bullet = PlayerBulletSprite::create();
    bullet->setPosition(getPosition());
    bullet->getPhysicsBody()->setVelocity(vec * GameConfig::PLAYER_BULLET_SPEED);
    // Add to layer
    layer->addChild(bullet);
}
