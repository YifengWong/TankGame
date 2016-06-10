#include "AliveSpriteBase.h"

USING_NS_CC;
using std::string;

AliveSpriteBase::AliveSpriteBase() {
}

AliveSpriteBase::~AliveSpriteBase() {
}

bool AliveSpriteBase::isDead() const {
    return hp.isZero();
}

const HPValue* AliveSpriteBase::getHP() const {
    return &hp;
}

void AliveSpriteBase::setHP(const HPValue &hp_) {
    hp = hp_;
}

void AliveSpriteBase::increaseHP(const int v) {
    hp.increase(v);
}

void AliveSpriteBase::decreaseHP(const int v) {
    hp.decrease(v);
}

void AliveSpriteBase::updateHpBar() {
    // Implement at subclass
}

void AliveSpriteBase::initHpBar(cocos2d::Layer *layer, const string &imageFilename) {
    Sprite* sp = Sprite::create(imageFilename);

    hpBar = cocos2d::ProgressTimer::create(sp);
    hpBar->setAnchorPoint(cocos2d::Vec2(0, 0));
    hpBar->setType(cocos2d::ProgressTimerType::BAR);
    hpBar->setBarChangeRate(cocos2d::Point(1, 0));
    hpBar->setMidpoint(cocos2d::Point(0, 1));
    hpBar->setPercentage(getHP()->getValue() / 10);

    if (layer) {
        layer->addChild(hpBar, 10);
    }

    hpBar->schedule([&](float f) {
        updateHpBar();
    }, "HpBarUpdateSchedule");
}

cocos2d::ProgressTimer* AliveSpriteBase::getHpBar() {
    return hpBar;
}

void AliveSpriteBase::removeHpBar() {
    hpBar->removeFromParent();
    hpBar = nullptr;
}
