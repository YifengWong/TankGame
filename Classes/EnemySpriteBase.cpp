#include "EnemySpriteBase.h"
#include "GameConfig.h"
#include "GameScene1Player.h"

void EnemySpriteBase::setGameScene(GameScene1Player *gameScene_) {
    gameScene = gameScene_;
}

GameScene1Player* EnemySpriteBase::getGameScene() {
    return gameScene;
}

void EnemySpriteBase::runAI() {
    schedule([&](float f) {
        makeAIDecision();
    }, GameConfig::ENEMY_DECISION_INTERVAL, "EnemyAISchedule");
}
