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
    physicBody->setTag(Constants::PLAYER_TAG);

    // Set player sprites
    player->setAnchorPoint(Vec2(0.5, 0.5));
    player->setPhysicsBody(physicBody);
    player->moveX = player->moveY = 0;

    return player;
}

void PlayerSprite::move() {
    if (moveX < 0 && !LayoutUtil::isReachBoundary(this, LEFT)) {
        setPosition(getPosition() + Vec2(moveX, 0));
    }
    if (moveX > 0 && !LayoutUtil::isReachBoundary(this, RIGHT)) {
        setPosition(getPosition() + Vec2(moveX, 0));
    }
    if (moveY < 0 && !LayoutUtil::isReachBoundary(this, DOWN)) {
        setPosition(getPosition() + Vec2(0, moveY));
    }
    if (moveY > 0 && !LayoutUtil::isReachBoundary(this, UP)) {
        setPosition(getPosition() + Vec2(0, moveY));
    }
}

void PlayerSprite::setMoveVal(const Direction &direc) {
    switch (direc) {
        case LEFT:
            if (!LayoutUtil::isReachBoundary(this, LEFT)) {
                setPosition(getPositionX() - 1, getPositionY());
            }
            moveX -= Constants::PLAYER_MOVE_DIST;
            break;
        case UP:
            if (!LayoutUtil::isReachBoundary(this, UP)) {
                setPosition(getPositionX(), getPositionY() + 1);
            }
            moveY += Constants::PLAYER_MOVE_DIST;
            break;
        case RIGHT:
            if (!LayoutUtil::isReachBoundary(this, RIGHT)) {
                setPosition(getPositionX() + 1, getPositionY());
            }
            moveX += Constants::PLAYER_MOVE_DIST;
            break;
        case DOWN:
            if (!LayoutUtil::isReachBoundary(this, DOWN)) {
                setPosition(getPositionX(), getPositionY() - 1);
            }
            moveY -= Constants::PLAYER_MOVE_DIST;
            break;
        default:
            break;
    }
}

void PlayerSprite::resetMoveVal(const Direction &direc) {
    switch (direc) {
        case LEFT:
            moveX += Constants::PLAYER_MOVE_DIST;
            break;
        case UP:
            moveY -= Constants::PLAYER_MOVE_DIST;
            break;
        case RIGHT:
            moveX -= Constants::PLAYER_MOVE_DIST;
            break;
        case DOWN:
            moveY += Constants::PLAYER_MOVE_DIST;
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
