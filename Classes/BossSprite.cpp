#include "BossSprite.h"
#include "EnemyBulletSprite.h"
#include "LayoutUtil.h"
#include "GameConfig.h"
#include "GameScene.h"

USING_NS_CC;

BossSprite* BossSprite::create(cocos2d::Layer *layer) {
	BossSprite *enemy = new (std::nothrow) BossSprite();
	if (enemy && enemy->initWithFile("boss.png")) {
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
		enemy->setLayer(layer);
		enemy->runAI();

		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

void BossSprite::fire(const cocos2d::Vec2 &target) {
	// Create unit direction vector
    auto vec = LayoutUtil::getUnitDirectionVector(getPosition(), target);
	// Add bullet
	auto bullet = EnemyBulletSprite::create();
	bullet->setPosition(getPosition());
	bullet->getPhysicsBody()->setVelocity(vec * GameConfig::ENEMY_BULLET_SPEED * 1.5);
	// Add to layer
	getLayer()->addChild(bullet);
}

void BossSprite::makeAIDecision() {
    if (this == nullptr || getLayer() == nullptr) return;

    if (rand() % 100 < 30) {
        if (rand() % 100 < 50) {
            if (GameScene::getPlayer() == nullptr) return;
            this->fire(GameScene::getPlayer()->getPosition());
        } else {
            this->fire(LayoutUtil::getPosition(static_cast<LayoutUtil::PositionType>(rand() % 13)));
        }
    }

    if (rand() % 100 < 80) {
        Vec2 vec;
        if (rand() % 100 < 50) {
            if (GameScene::getPlayer() == nullptr) return;
            vec = LayoutUtil::getUnitDirectionVector(this->getPosition(),
                                                     GameScene::getPlayer()->getPosition());
        } else {
            auto pos = static_cast<LayoutUtil::PositionType>(rand() % 13);
            vec = LayoutUtil::getUnitDirectionVector(this->getPosition(),
                                                     LayoutUtil::getPosition(pos));
        }
        this->getPhysicsBody()->setVelocity(vec * GameConfig::ENEMY_MOVE_UNIT);
    }
}
