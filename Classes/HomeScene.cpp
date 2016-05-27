#include "HomeScene.h"
#include "GameScene.h"
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

    addStartBtn();

    // TODO Home scene design

    return true;
}

void HomeScene::addStartBtn() {
    auto startBtn = Button::create();
    startBtn->setTitleText("Start");
    startBtn->setTitleFontSize(30);
    startBtn->setPosition(LayoutUtil::getCenterPosition());
    startBtn->addClickEventListener([](Ref* pSender) {
        Director::getInstance()->replaceScene(GameScene::createScene());
    });
    addChild(startBtn, 0);
}
