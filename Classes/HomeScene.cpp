#include "HomeScene.h"
#include "VSGameScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "GameUtil.h"

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
    startBtn->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER));
    startBtn->addClickEventListener([](Ref* pSender) {
        Director::getInstance()->replaceScene(GameScene::createScene());
    });
    addChild(startBtn, 0);

	auto startVSBtn = Button::create();
	startVSBtn->setTitleText("StartVS");
	startVSBtn->setTitleFontSize(30);
	startVSBtn->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER) + Vec2(0, -100));
	startVSBtn->addClickEventListener([](Ref* pSender) {
		Director::getInstance()->replaceScene(VSGameScene::createScene());
	});
	addChild(startVSBtn, 0);
}
