#pragma once

/*
Class for sprite's HP
*/
class HPValue {
public:
    HPValue(const int max_ = 0, const int val_ = 0);

    void increase(const int v);

    void decrease(const int v);

    void setValue(const int v);

    int getValue() const;

    void setMax(const int m);

    int getMax() const;

    bool isZero() const;

private:
    int max;
    int value;
};
