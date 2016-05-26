#include "HomeScene.h"
#include "ui/CocosGUI.h"
#include "LayoutUtil.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* HomeScene::createScene() {
    auto layer = HomeScene::create();
    auto scene = Scene::create();
    scene->addChild(layer);
    return scene;
}

bool HomeScene::init() {
    if (!Layer::init()) {
        return false;
    }

    initStartBtn();

    return true;
}

void HomeScene::initStartBtn() {
    auto startBtn = Button::create();
    startBtn->setTitleText("Start");
    startBtn->setTitleFontSize(30);
    startBtn->setPosition(LayoutUtil::getCenterPosition());
    startBtn->addClickEventListener([](Ref* pSender) {
        Director::getInstance()->end();
    });
    this->addChild(startBtn, 0);
}
