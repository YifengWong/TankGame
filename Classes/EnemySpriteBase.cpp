#include "EnemySpriteBase.h"
#include "GameConfig.h"
#include "GameScene1Player.h"


EnemySpriteBase::EnemySpriteBase() {
	//setHpBar();
}

EnemySpriteBase::~EnemySpriteBase() {
	//removeHpBar();
}

void EnemySpriteBase::runAI() {
    schedule([&](float f) {
        makeAIDecision();
    }, GameConfig::ENEMY_DECISION_INTERVAL, "EnemyAISchedule");
}

void EnemySpriteBase::onRemove() {
    SpriteBase::onRemove();
    removeHpBar();
    auto scene = dynamic_cast<GameScene1Player*>(getGameScene());
    if (scene) {
        scene->decreaseEnemyCnt();
    }
}

void EnemySpriteBase::updateHpBar() {
	if (getHpBar()) {
        getHpBar()->setPosition(this->getPosition() + cocos2d::Vec2(-7, -15));
        getHpBar()->setPercentage(this->getHP()->getValue() / 10);
	}
}
