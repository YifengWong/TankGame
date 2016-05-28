#include "EnemySprite.h"
#include "EnemyBulletSprite.h"
#include "LayoutUtil.h"
#include "Constants.h"
#include "GameScene.h"

USING_NS_CC;

EnemySprite* EnemySprite::create(cocos2d::Layer *layer) {
    EnemySprite *enemy = new (std::nothrow) EnemySprite();
    if (enemy && enemy->initWithFile("enemy.png")) {
        enemy->autorelease();

        // Create physics body
        auto physicBody = PhysicsBody::createBox(enemy->getContentSize());
        // Set group and bitmasks
        physicBody->setGroup(Constants::ENEMY_PHYSIC_GROUP);
        physicBody->setCategoryBitmask(Constants::ENEMY_PHYSIC_CATEGORY_BM);
        physicBody->setCollisionBitmask(Constants::ENEMY_PHYSIC_COLLISION_BM);
        physicBody->setContactTestBitmask(Constants::ENEMY_PHYSIC_CONTACT_BM);
        physicBody->setRotationEnable(false);
        physicBody->setTag(Constants::ENEMY_TAG);

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
    bullet->getPhysicsBody()->setVelocity(directionVec * Constants::ENEMY_BULLET_SPEED);
    // Add to layer
    layer->addChild(bullet);
}

void EnemySprite::scheduleAI() {
    // The third param is not used
    schedule([&](float f) {
        if (this == nullptr || layer == nullptr
            || GameScene::getPlayer() == nullptr) return;

        // TODO Enemy AI design
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
            this->getPhysicsBody()->setVelocity(vec * Constants::ENEMY_MOVE_UNIT);
        }

    }, 1, "EnemyAISchedule");
}

void EnemySprite::setLayer(cocos2d::Layer *layer_) {
    layer = layer_;
}
