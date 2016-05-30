#include "WallSprite.h"
#include "GameParam.h"

USING_NS_CC;

WallSprite* WallSprite::create(const bool &breakable) {
    WallSprite *wall = new (std::nothrow) WallSprite();
    if (wall) {
        bool suc = breakable ? wall->initWithFile("wall_breakable.png")
            : wall->initWithFile("wall_unbreakable.png");
        if (suc) {
            wall->autorelease();

            // Create physics body
            auto physicBody = PhysicsBody::createBox(wall->getContentSize(), PhysicsMaterial(0, 2, 0));
            physicBody->setDynamic(false);
            // Set group and bitmasks
            physicBody->setGroup(GameParam::WALL_PHYSIC_GROUP);
            physicBody->setCategoryBitmask(GameParam::WALL_PHYSIC_CATEGORY_BM);
            physicBody->setCollisionBitmask(GameParam::WALL_PHYSIC_COLLISION_BM);
            physicBody->setContactTestBitmask(GameParam::WALL_PHYSIC_CONTACT_BM);
            physicBody->setTag(GameParam::WALL_TAG);

            // Set player sprites
            wall->setAnchorPoint(Vec2(0.5, 0.5));
            wall->setPhysicsBody(physicBody);
            wall->setBreakable(breakable);

            return wall;
        }
    }
    CC_SAFE_DELETE(wall);
    return nullptr;
}

void WallSprite::setBreakable(const bool &b) {
    breakable = b;
}

bool WallSprite::isBreakable() {
    return breakable;
}
