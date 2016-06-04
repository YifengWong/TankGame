#include "GameUtil.h"
#include "EnemyBossSprite.h"
#include "EnemyNormalSprite.h"
#include "SimpleAudioEngine.h"
#include "GameConfig.h"
#include "GameScene1Player.h"
#include "GameScene2Player.h"
#include "HomeScene.h"

USING_NS_CC;
using namespace CocosDenshion;

void GameUtil::returnToHome() {
    PlayerBulletSprite::clearBulletCount();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    Director::getInstance()->replaceScene(HomeScene::createScene());
}

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
    const double offset = 0.5 * 0.2 * (visibleSize.width - origin.x + visibleSize.height - origin.y);
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

Vec2 GameUtil::getPosition(const int &row, const int &column) {
    if (!(row >= 0 && row <= GameConfig::WINDOW_ROW_NUM 
        && column >= 0 && column <= GameConfig::WINDOW_COLUMN_NUM)) {
        return getPosition(PositionType::LEFT_BOTTOM);
    }
    auto origin = getOrigin();
    auto visibleSize = getVisibleSize();
    double gridWidth = (visibleSize.width - origin.x) / GameConfig::WINDOW_COLUMN_NUM;
    double gridHeight = (visibleSize.height) / GameConfig::WINDOW_ROW_NUM;
    double x = origin.x + (column + 0.5) * gridWidth;
    double y = origin.y + (GameConfig::WINDOW_ROW_NUM - row - 1 + 0.5) * gridHeight;
    return Vec2(x, y);
}

void GameUtil::preloadMusic() {
    //SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/xxx");
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(GameConfig::MUSIC_BG_VOLUME);
    SimpleAudioEngine::getInstance()->preloadEffect("music/bullet_hit.wav");
    SimpleAudioEngine::getInstance()->setEffectsVolume(GameConfig::MUSIC_EFFECT_VOLUME);
}

void GameUtil::playEffect(const MusicEffectType &effectType) {
    if (GameConfig::MUTE) return;
    switch (effectType) {
        case BULLET_HIT:
            SimpleAudioEngine::getInstance()->playEffect("music/bullet_hit.wav");
            break;
        default:
            break;
    }
}

void GameUtil::playBgMusic(const MusicBgType &bgType) {
    if (GameConfig::MUTE) return;
    switch (bgType) {
        case HOME_PAGE:
            //SimpleAudioEngine::getInstance()->playBackgroundMusic("music/xxx");
            break;
        default:
            break;
    }
}

void GameUtil::addParticles(cocos2d::Layer *layer, const cocos2d::Vec2 &pos, const ParticleType &type) {
    if (!layer) return;
    ParticleSystemQuad *ps;
    switch (type) {
        case EXPLODE:
            ps = ParticleSystemQuad::create("explode.plist");
            break;
        default:
            return;
            break;
    }
    ps->setPosition(pos);
    layer->addChild(ps);
}
