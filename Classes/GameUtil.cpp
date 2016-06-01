#include "GameUtil.h"
#include "EnemyBossSprite.h"
#include "EnemyNormalSprite.h"

USING_NS_CC;

Vec2 GameUtil::getOrigin() {
    return Director::getInstance()->getVisibleOrigin();
}

Size GameUtil::getVisibleSize() {
    return Director::getInstance()->getVisibleSize();
}

bool GameUtil::isReachBoundary(const cocos2d::Sprite *sprite, const Direction &boundDirec) {
    if (sprite == nullptr) return true;
    int x = sprite->getPosition().x;
    int y = sprite->getPosition().y;
    int width = sprite->getContentSize().width;
    int height = sprite->getContentSize().height;
    auto origin = getOrigin();
    auto visibleSize = getVisibleSize();
    const int offset = 3;

    bool reach = false;
    switch (boundDirec) {
        case LEFT:
            if (x - origin.x <= width / 2 + offset) reach = true;
            break;
        case UP:
            if (origin.y + visibleSize.height - y <= height / 2 + offset) reach = true;
            break;
        case RIGHT:
            if (origin.x + visibleSize.width - x <= width / 2 + offset) reach = true;
            break;
        case DOWN:
            if (y - origin.y <= height / 2 + offset) reach = true;
            break;
        default:
            break;
    }
    return reach;
}

cocos2d::Vec2 GameUtil::getUnitDirectionVector(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to) {
    auto vec = to - from;
    vec.normalize();
    return vec;
}

bool GameUtil::isNormalEnemy(EnemySpriteBase *enemy) {
    return nullptr != dynamic_cast<EnemyNormalSprite*>(enemy);
}

bool GameUtil::isBossEnemy(EnemySpriteBase *enemy) {
    return nullptr != dynamic_cast<EnemyBossSprite*>(enemy);
}

Vec2 GameUtil::getPosition(const PositionType &type) {
    auto origin = getOrigin();
    auto visibleSize = getVisibleSize();
    const int offset = 70;
    switch (type) {
        case LEFT_TOP:
            return Vec2(origin.x + offset,
                        origin.y + visibleSize.height - offset);
            break;
        case LEFT_BOTTOM:
            return Vec2(origin.x + offset,
                        origin.y + offset);
            break;
        case RIGHT_TOP:
            return Vec2(origin.x + visibleSize.width - offset,
                        origin.y + visibleSize.height - offset);
            break;
        case RIGHT_BOTTOM:
            return Vec2(origin.x + visibleSize.width - offset,
                        origin.y + offset);
            break;
        case CENTER_LEFT:
            return Vec2(origin.x + offset,
                        origin.y + visibleSize.height / 2);
            break;
        case CENTER_RIGHT:
            return Vec2(origin.x + visibleSize.width - offset,
                        origin.y + visibleSize.height / 2);
            break;
        case CENTER_TOP:
            return Vec2(origin.x + visibleSize.width / 2,
                        origin.y + visibleSize.height - offset);
            break;
        case CENTER_DOWN:
            return Vec2(origin.x + visibleSize.width / 2,
                        origin.y + offset);
            break;
        case CORNER_LEFT_TOP:
            return Vec2(origin.x,
                        origin.y + visibleSize.height);
            break;
        case CORNER_RIGHT_TOP:
            return Vec2(origin.x + visibleSize.width,
                        origin.y + visibleSize.height);
            break;
        case CORNER_RIGHT_BOTTOM:
            return Vec2(origin.x + visibleSize.width,
                        origin.y);
            break;
        case CORNER_LEFT_BOTTOM:
            return Vec2(origin.x,
                        origin.y);
            break;
        case EDGE_CENTER_LEFT:
            return Vec2(origin.x,
                        origin.y + visibleSize.height / 2);
            break;
        case EDGE_CENTER_TOP:
            return Vec2(origin.x + visibleSize.width / 2,
                        origin.y + visibleSize.height);
            break;
        case EDGE_CENTER_RIGHT:
            return Vec2(origin.x + visibleSize.width,
                        origin.y + visibleSize.height / 2);
            break;
        case EDGE_CENTER_BOTTOM:
            return Vec2(origin.x + visibleSize.width / 2,
                        origin.y);
            break;
        case CENTER:
        default:
            return Vec2(origin.x + visibleSize.width / 2,
                        origin.y + visibleSize.height / 2);
            break;
    }
}

int GameUtil::getPositionTypeCount() {
    return 17;
}