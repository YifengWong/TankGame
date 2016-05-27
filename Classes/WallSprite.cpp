#include "WallSprite.h"
#include "Constants.h"

USING_NS_CC;

WallSprite* WallSprite::create() {
    auto sprite = Sprite::create("wall.png");
    auto wall = static_cast<WallSprite*>(sprite);

    // Create physics body
    auto physicBody = PhysicsBody::createBox(wall->getContentSize(), PhysicsMaterial(0, 2, 0));
    physicBody->setDynamic(false);
    // Set group and bitmasks
    physicBody->setGroup(Constants::WALL_PHYSIC_GROUP);
    physicBody->setCategoryBitmask(Constants::WALL_PHYSIC_CATEGORY_BM);
    physicBody->setCollisionBitmask(Constants::WALL_PHYSIC_COLLISION_BM);
    physicBody->setContactTestBitmask(Constants::WALL_PHYSIC_CONTACT_BM);
    physicBody->setTag(Constants::WALL_TAG);

    // Set player sprites
    wall->setAnchorPoint(Vec2(0.5, 0.5));
    wall->setPhysicsBody(physicBody);

    return wall;
}
