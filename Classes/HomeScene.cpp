#include "HomeScene.h"
#include "GameScene2Player.h"
#include "GameScene1Player.h"
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

    addStartBtns();

    // TODO Home scene design

    return true;
}

void HomeScene::addStartBtns() {
    auto startBtn = Button::create();
    startBtn->setTitleText("1 Player");
    startBtn->setTitleFontSize(30);
    startBtn->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER) + Vec2(0, 30));
    startBtn->addClickEventListener([](Ref* pSender) {
        Director::getInstance()->replaceScene(GameScene1Player::createScene());
    });
    addChild(startBtn, 0);

	auto startVSBtn = Button::create();
	startVSBtn->setTitleText("2 Player");
	startVSBtn->setTitleFontSize(30);
	startVSBtn->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER) + Vec2(0, -30));
	startVSBtn->addClickEventListener([](Ref* pSender) {
		Director::getInstance()->replaceScene(GameScene2Player::createScene());
	});
	addChild(startVSBtn, 0);
}
