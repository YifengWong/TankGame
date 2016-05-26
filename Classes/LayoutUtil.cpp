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
