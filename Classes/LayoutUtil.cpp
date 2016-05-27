#include "LayoutUtil.h"

USING_NS_CC;

Vec2 LayoutUtil::getCenterPosition() {
    auto origin = getOrigin();
    auto visibleSize = getVisibleSize();
    return Vec2(origin.x + visibleSize.width / 2,
                origin.y + visibleSize.height / 2);
}

Vec2 LayoutUtil::getOrigin() {
    return Director::getInstance()->getVisibleOrigin();
}

Size LayoutUtil::getVisibleSize() {
    return Director::getInstance()->getVisibleSize();
}

bool LayoutUtil::isReachBoundary(const cocos2d::Sprite *sprite, const Direction &boundDirec) {
    if (sprite == NULL) return true;
    int x = sprite->getPosition().x;
    int y = sprite->getPosition().y;
    int width = sprite->getContentSize().width;
    int height = sprite->getContentSize().height;
    auto origin = getOrigin();
    auto visibleSize = getVisibleSize();

    bool reach = false;
    switch (boundDirec) {
        case LEFT:
            if (x - origin.x <= width / 2) reach = true;
            break;
        case UP:
            if (origin.y + visibleSize.height - y <= height / 2) reach = true;
            break;
        case RIGHT:
            if (origin.x + visibleSize.width - x <= width / 2) reach = true;
            break;
        case DOWN:
            if (y - origin.y <= height / 2) reach = true;
            break;
        default:
            break;
    }
    return reach;
}
