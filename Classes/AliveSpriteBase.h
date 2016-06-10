#pragma once

#include "HPValue.h"
#include <string>

class AliveSpriteBase {
public:
    AliveSpriteBase();
    virtual ~AliveSpriteBase();

    /*
    Check if the sprite is dead.
    Author: ChuyangLiu
    */
    bool isDead() const;

    /*
    Return the hp value.
    Author: ChuyangLiu
    */
    const HPValue* getHP() const;

    /*
    Set the hp value.
    Author: ChuyangLiu
    */
    void setHP(const HPValue &hp_);

    /*
    Increase the hp value.
    Author: ChuyangLiu
    */
    void increaseHP(const int v);

    /*
    Decrease the hp value.
    Author: ChuyangLiu
    */
    void decreaseHP(const int v);

protected:
    /*
    Initialize the hp bar
    Author: YifengWong & ChuyangLiu
    */
    void initHpBar(cocos2d::Layer *layer, const std::string &imageFilename);

    /*
    Update the hp bar at every frame
    Author: YifengWong & ChuyangLiu
    */
    virtual void updateHpBar();

    /*
    Return the hp bar object
    Author: ChuyangLiu
    */
    cocos2d::ProgressTimer* getHpBar();

    /*
    Remove the hp bar object
    Author: YifengWong & ChuyangLiu
    */
    void removeHpBar();

private:
    HPValue hp;

    cocos2d::ProgressTimer* hpBar = nullptr;
};
