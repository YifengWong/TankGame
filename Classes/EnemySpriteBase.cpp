#include "EnemySpriteBase.h"
#include "GameConfig.h"

void EnemySpriteBase::setLayer(cocos2d::Layer *layer_) {
    layer = layer_;
}

cocos2d::Layer* EnemySpriteBase::getLayer() {
    return layer;
}

void EnemySpriteBase::runAI() {
    schedule([&](float f) {
        makeAIDecision();
    }, GameConfig::AI_DECISION_INTERVAL, "EnemyAISchedule");
}
