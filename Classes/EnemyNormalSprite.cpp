#include "EnemyNormalSprite.h"
#include "EnemyBulletSprite.h"
#include "GameUtil.h"
#include "GameConfig.h"
#include "GameScene1Player.h"

USING_NS_CC;

EnemyNormalSprite::EnemyNormalSprite() {
}

EnemyNormalSprite::~EnemyNormalSprite() {
}

EnemyNormalSprite* EnemyNormalSprite::create(GameScene1Player *scene) {
    EnemyNormalSprite *enemy = new (std::nothrow) EnemyNormalSprite();
    if (enemy && enemy->initWithFile("enemy.png")) {
        enemy->autorelease();

        // Create physics body
        auto physicBody = PhysicsBody::createBox(enemy->getContentSize());
        // Set group and bitmasks
        physicBody->setGroup(GameConfig::ENEMY_PHYSIC_GROUP);
        physicBody->setCategoryBitmask(GameConfig::ENEMY_PHYSIC_CATEGORY_BM);
        physicBody->setCollisionBitmask(GameConfig::ENEMY_PHYSIC_COLLISION_BM);
        physicBody->setContactTestBitmask(GameConfig::ENEMY_PHYSIC_CONTACT_BM);
        physicBody->setRotationEnable(false);
        physicBody->setTag(GameConfig::ENEMY_TAG);

        // Set player sprites
        enemy->setAnchorPoint(Vec2(0.5, 0.5));
        enemy->setPhysicsBody(physicBody);
        enemy->setGameScene(scene);
        enemy->runAI();
        enemy->setHP(HPValue(GameConfig::ENEMY_NORMAL_MAX_HP, GameConfig::ENEMY_NORMAL_INIT_HP));

        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return nullptr;
}

void EnemyNormalSprite::fire(const cocos2d::Vec2 &target) {
    // Create unit direction vector
    auto vec = GameUtil::getUnitDirectionVector(getPosition(), target);
    // Add bullet
    auto bullet = EnemyBulletSprite::create();
    bullet->setPosition(getPosition());
    bullet->getPhysicsBody()->setVelocity(vec * GameConfig::ENEMY_NORMAL_BULLET_SPEED);
    // Add to layer
    getGameScene()->addChild(bullet);
}

void EnemyNormalSprite::makeAIDecision() {
    if (this == nullptr || getGameScene() == nullptr) return;

    if (rand() % 100 < 30) {
        if (rand() % 100 < 50) {
            if (getGameScene()->getPlayer() == nullptr) return;
            this->fire(getGameScene()->getPlayer()->getPosition());
        } else {
            this->fire(GameUtil::getPosition(static_cast<GameUtil::PositionType>(
                rand() % GameUtil::getPositionTypeCount())));
        }
    }

    if (rand() % 100 < 80) {
        Vec2 vec;
        if (rand() % 100 < 50) {
            if (getGameScene()->getPlayer() == nullptr) return;
            vec = GameUtil::getUnitDirectionVector(this->getPosition(),
                                                   getGameScene()->getPlayer()->getPosition());
        } else {
            auto pos = static_cast<GameUtil::PositionType>(rand() % GameUtil::getPositionTypeCount());
            vec = GameUtil::getUnitDirectionVector(this->getPosition(),
                                                     GameUtil::getPosition(pos));
        }
        this->getPhysicsBody()->setVelocity(vec * GameConfig::ENEMY_NORMAL_MOVE_SPEED);
    }
}

