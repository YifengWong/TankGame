#include "HomeScene.h"
#include "GameScene2Player.h"
#include "GameScene1Player.h"
#include "HelpScene.h"
#include "ui/CocosGUI.h"
#include "GameUtil.h"
#include "GameConfig.h"
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
    addCheckpointBtn();
	addHelpBtn();

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

void HomeScene::addCheckpointBtn() {
    curCptBtn = Button::create();
    curCptBtn->setTitleText("Current stage: " + GameUtil::convertToString(GameConfig::CURRENT_STAGE));
    curCptBtn->setPosition(GameUtil::getPosition(GameUtil::PositionType::RIGHT_BOTTOM) + Vec2(0, -20));
    curCptBtn->addClickEventListener([&](Ref* pSender) {
        auto max = GameScriptFactory::getInstance()->getStageCount();
        if (GameConfig::CURRENT_STAGE == max - 1) {
            GameConfig::CURRENT_STAGE = 0;
        } else {
            ++GameConfig::CURRENT_STAGE;
        }
        curCptBtn->setTitleText("Current stage: " + GameUtil::convertToString(GameConfig::CURRENT_STAGE));
    });
    addChild(curCptBtn);
}

void HomeScene::addHelpBtn() {
	auto helpBtn = Button::create();
	helpBtn->setTitleText("Help");
	helpBtn->setTitleFontSize(30);
	helpBtn->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER) + Vec2(0, -90));
	helpBtn->addClickEventListener([](Ref* pSender) {
		Director::getInstance()->replaceScene(HelpScene::createScene());
	});
	addChild(helpBtn);
}