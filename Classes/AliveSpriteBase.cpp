#include "AliveSpriteBase.h"

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
