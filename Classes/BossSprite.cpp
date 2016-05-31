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
		auto physicBody = PhysicsBody::createBox(enemy->getContentSize(), PhysicsMaterial(0, 2, 0));
		physicBody->setDynamic(false);
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
		enemy->scheduleAI();

		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

void BossSprite::fire(const cocos2d::Vec2 &target) {
	// Create unit direction vector
	auto directionVec = target - getPosition();
	directionVec.normalize();
	// Add bullet
	auto bullet = EnemyBulletSprite::create();
	bullet->setPosition(getPosition());
	bullet->getPhysicsBody()->setVelocity(directionVec * GameConfig::ENEMY_BULLET_SPEED * 1.5);
	// Add to layer
	layer->addChild(bullet);
}

void BossSprite::scheduleAI() {
	// The third param is not used
	schedule([&](float f) {
		if (this == nullptr || layer == nullptr
			|| GameScene::getPlayer() == nullptr) return;

		// AI decision
		this->fire(GameScene::getPlayer()->getPosition());

	}, 1, "EnemyAISchedule");
}

void BossSprite::setLayer(cocos2d::Layer *layer_) {
	layer = layer_;
}
