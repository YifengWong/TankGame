#include "PlayerSpriteBase.h"

PlayerSpriteBase::PlayerSpriteBase() {
}

PlayerSpriteBase::~PlayerSpriteBase() {
}

void PlayerSpriteBase::onRemove() {
    SpriteBase::onRemove();
    removeHpBar();
}

void PlayerSpriteBase::updateHpBar() {
    if (getHpBar()) {
        getHpBar()->setPosition(this->getPosition() + cocos2d::Vec2(-7, -15));
        getHpBar()->setPercentage(this->getHP()->getValue() / 10);
    }
}