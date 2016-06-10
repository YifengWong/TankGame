#include "EnemySpriteBase.h"
#include "GameConfig.h"
#include "GameScene1Player.h"


EnemySpriteBase::EnemySpriteBase() {
	setHpBar();
}

EnemySpriteBase::~EnemySpriteBase() {
	removeHpBar();
}

void EnemySpriteBase::runAI() {
    schedule([&](float f) {
        makeAIDecision();
    }, GameConfig::ENEMY_DECISION_INTERVAL, "EnemyAISchedule");
}

void EnemySpriteBase::onRemove() {
    getGameScene()->decreaseEnemyCnt();
}

void EnemySpriteBase::removeHpBar() {
	hpSprite->removeFromParent();
	hpSprite = nullptr;
}

void EnemySpriteBase::showHpBar() {
	getGameScene()->addChild(hpSprite, 1);
	schedule([&](float f) {
		updateHpBar();
	}, "HpBarUpdateSchedule");
}

void EnemySpriteBase::updateHpBar() {
	if (hpSprite) {
		hpSprite->setPosition(this->getPosition() + cocos2d::Vec2(-7, -15));
		hpSprite->setPercentage(this->getHP()->getValue() / 10);
	}
}

void EnemySpriteBase::setHpBar() {
	cocos2d::Sprite* sp = cocos2d::Sprite::create("hp_bar.png");

	hpSprite = cocos2d::ProgressTimer::create(sp);
	hpSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
	hpSprite->setType(cocos2d::ProgressTimerType::BAR);
	hpSprite->setBarChangeRate(cocos2d::Point(1, 0));
	hpSprite->setMidpoint(cocos2d::Point(0, 1));
	hpSprite->setPercentage(getHP()->getValue() / 10);
}