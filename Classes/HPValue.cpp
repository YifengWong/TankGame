#include "HPValue.h"

HPValue::HPValue(const int max_, const int val_) : max(max_), value(val_) {}

void HPValue::increase(const int v) {
    value += v;
    if (value > max) {
        value = max;
    }
}

void HPValue::decrease(const int v) {
    value -= v;
    if (value < 0) {
        value = 0;
    }
}

void HPValue::setValue(const int v) {
    if (v > max) {
        value = max;
    } else if (v < 0) {
        value = 0;
    } else {
        value = v;
    }
}

int HPValue::getValue() {
    return value;
}

void HPValue::setMax(const int m) {
    max = m;
}

int HPValue::getMax() {
    return max;
}

bool HPValue::isZero() {
    return value == 0;
}
