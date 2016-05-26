#include "PlayerSprite.h"
#include "Constants.h"

USING_NS_CC;

PlayerSprite* PlayerSprite::create() {
    auto sprite = Sprite::create("player_test.png");
    auto player = static_cast<PlayerSprite*>(sprite);

    // Create physics body
    auto physicBody = PhysicsBody::createCircle(player->getContentSize().height / 2);
    // Set group and bitmasks
    physicBody->setGroup(Constants::PLAYER_PHYSIC_GROUP);
    physicBody->setCategoryBitmask(Constants::PLAYER_PHYSIC_CATEGORY_BM);
    physicBody->setContactTestBitmask(Constants::PLAYER_PHYSIC_CONTACT_BM);

    // Set player sprites
    player->setAnchorPoint(Vec2(0.5, 0.5));
    player->setPhysicsBody(physicBody);

    return player;
}

void PlayerSprite::startMove(const Direction &direc) {
    auto physicBody = getPhysicsBody();
    if (physicBody == NULL) return;
    switch (direc) {
        case PlayerSprite::LEFT:
            physicBody->setVelocity(Point(-Constants::PLAYER_MOVE_DIST, physicBody->getVelocity().y));
            break;
        case PlayerSprite::UP:
            physicBody->setVelocity(Point(physicBody->getVelocity().x, Constants::PLAYER_MOVE_DIST));
            break;
        case PlayerSprite::RIGHT:
            physicBody->setVelocity(Point(Constants::PLAYER_MOVE_DIST, physicBody->getVelocity().y));
            break;
        case PlayerSprite::DOWN:
            physicBody->setVelocity(Point(physicBody->getVelocity().x, -Constants::PLAYER_MOVE_DIST));
            break;
        default:
            break;
    }
}

void PlayerSprite::stopMove(const Direction &direc) {
    auto physicBody = getPhysicsBody();
    // If does not have a physic body 
    // or the body is already stopped, exit
    if (physicBody == NULL || physicBody->getVelocity() == Vec2(0, 0)) return;

    switch (direc) {
        case PlayerSprite::LEFT:
            physicBody->setVelocity(physicBody->getVelocity() + Point(Constants::PLAYER_MOVE_DIST, 0));
            break;
        case PlayerSprite::UP:
            physicBody->setVelocity(physicBody->getVelocity() + Point(0, -Constants::PLAYER_MOVE_DIST));
            break;
        case PlayerSprite::RIGHT:
            physicBody->setVelocity(physicBody->getVelocity() + Point(-Constants::PLAYER_MOVE_DIST, 0));
            break;
        case PlayerSprite::DOWN:
            physicBody->setVelocity(physicBody->getVelocity() + Point(0, Constants::PLAYER_MOVE_DIST));
            break;
        default:
            break;
    }
}
