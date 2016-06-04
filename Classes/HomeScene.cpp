#include "HomeScene.h"
#include "GameScene2Player.h"
#include "GameScene1Player.h"
#include "ui/CocosGUI.h"
#include "GameUtil.h"
#include "GameScriptFactory.h"
#include <string>

USING_NS_CC;
using std::string;
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
    addScriptInfo();

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
    addChild(startBtn);

	auto startVSBtn = Button::create();
	startVSBtn->setTitleText("2 Player");
	startVSBtn->setTitleFontSize(30);
	startVSBtn->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER) + Vec2(0, -30));
	startVSBtn->addClickEventListener([](Ref* pSender) {
		Director::getInstance()->replaceScene(GameScene2Player::createScene());
	});
	addChild(startVSBtn);
}

void HomeScene::addScriptInfo() {
    auto cptNum = Label::create();
    auto cptCnt = GameScriptFactory::getInstance()->getCheckpointsCount();
    cptNum->setString("Level number: " + GameUtil::convertToString(cptCnt));
    cptNum->setPosition(GameUtil::getPosition(GameUtil::PositionType::RIGHT_BOTTOM) + Vec2(0, -20));
    addChild(cptNum);
}
