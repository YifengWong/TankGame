#include "EnemySprite.h"
#include "EnemyBulletSprite.h"
#include "LayoutUtil.h"
#include "GameParam.h"
#include "GameScene.h"

USING_NS_CC;

EnemySprite* EnemySprite::create(cocos2d::Layer *layer) {
    EnemySprite *enemy = new (std::nothrow) EnemySprite();
    if (enemy && enemy->initWithFile("enemy.png")) {
        enemy->autorelease();

        // Create physics body
        auto physicBody = PhysicsBody::createBox(enemy->getContentSize());
        // Set group and bitmasks
        physicBody->setGroup(GameParam::ENEMY_PHYSIC_GROUP);
        physicBody->setCategoryBitmask(GameParam::ENEMY_PHYSIC_CATEGORY_BM);
        physicBody->setCollisionBitmask(GameParam::ENEMY_PHYSIC_COLLISION_BM);
        physicBody->setContactTestBitmask(GameParam::ENEMY_PHYSIC_CONTACT_BM);
        physicBody->setRotationEnable(false);
        physicBody->setTag(GameParam::ENEMY_TAG);

        // Set player sprites
        enemy->setAnchorPoint(Vec2(0.5, 0.5));
        enemy->setPhysicsBody(physicBody);
        enemy->setLayer(layer);
        enemy->scheduleAI();

        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return nullptr;
}

void EnemySprite::fire(const cocos2d::Vec2 &target) {
    // Create unit direction vector
    auto directionVec = target - getPosition();
    directionVec.normalize();
    // Add bullet
    auto bullet = EnemyBulletSprite::create();
    bullet->setPosition(getPosition());
    bullet->getPhysicsBody()->setVelocity(directionVec * GameParam::ENEMY_BULLET_SPEED);
    // Add to layer
    layer->addChild(bullet);
}

void EnemySprite::scheduleAI() {
    // The third param is not used
    schedule([&](float f) {
        if (this == nullptr || layer == nullptr
            || GameScene::getPlayer() == nullptr) return;

        // AI decision
        if (rand() % 100 < 30) {
            if (rand() % 100 < 50) {
                this->fire(GameScene::getPlayer()->getPosition());
            } else {
                this->fire(LayoutUtil::getPosition(LayoutUtil::PositionType::CENTER));
            }
        }

        if (rand() % 100 < 50) {
            Vec2 vec;
            if (rand() % 100 < 50) {
                vec = LayoutUtil::getUnitDirectionVector(this->getPosition(),
                                                         GameScene::getPlayer()->getPosition());
            } else {
                auto pos = static_cast<LayoutUtil::PositionType>(rand() % 5);
                vec = LayoutUtil::getUnitDirectionVector(this->getPosition(),
                                                         LayoutUtil::getPosition(pos));
            }
            this->getPhysicsBody()->setVelocity(vec * GameParam::ENEMY_MOVE_UNIT);
        }

    }, 1, "EnemyAISchedule");
}

void EnemySprite::setLayer(cocos2d::Layer *layer_) {
    layer = layer_;
}
