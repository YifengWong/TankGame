#include "EnemySpriteBase.h"
#include "GameConfig.h"
#include "GameScene1Player.h"

EnemySpriteBase::EnemySpriteBase() {
}

EnemySpriteBase::~EnemySpriteBase() {
}

void EnemySpriteBase::runAI() {
    schedule([&](float f) {
        makeAIDecision();
    }, GameConfig::ENEMY_DECISION_INTERVAL, "EnemyAISchedule");
}

void EnemySpriteBase::onRemove() {
    getGameScene()->decreaseEnemyCnt();
}
