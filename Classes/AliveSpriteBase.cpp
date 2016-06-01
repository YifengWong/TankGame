#include "AliveSpriteBase.h"

bool AliveSpriteBase::isDead() {
    return hp.isZero();
}

HPValue* AliveSpriteBase::getHP() {
    return &hp;
}

void AliveSpriteBase::setHP(const HPValue &hp_) {
    hp = hp;
}
