#include "HelpScene.h"
#include "GameScene2Player.h"
#include "GameScene1Player.h"
#include "ui/CocosGUI.h"
#include "GameUtil.h"
#include "GameConfig.h"
#include "GameScriptFactory.h"
#include <string>

USING_NS_CC;
using std::string;
using namespace cocos2d::ui;

Scene* HelpScene::createScene() {
	auto layer = HelpScene::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}

bool HelpScene::init() {
	if (!Layer::init()) {
		return false;
	}

	addHelp();
	addKeyboardListener();

	return true;
}


void HelpScene::addHelp() {
	string player1 = "player1:\n      Move:W A S D \n      Shoot: Left Click \n\n";
	string player2_1 = "player 2:\n  Yellow:\n      Move: W A S D \n      Shoot: Space \n";
	string player2_2 = "   Red:\n      Move: direction key \n      Shoot: Enter \n\n";
	auto label = Label::createWithTTF(player1 + player2_1 + player2_2, 
										"fonts/arial.ttf", 18);

	label->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER));

	addChild(label, 1);

	auto backBtn = Button::create();
	backBtn->setTitleText("Back: Home \n");
	backBtn->setTitleFontSize(18);
	backBtn->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER) + Vec2(0, -130));
	backBtn->addClickEventListener([](Ref* pSender) {
		GameUtil::toHomeScene();
	});
	addChild(backBtn, 2);
}

void HelpScene::addKeyboardListener() {
	auto keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event) {
		switch (code) {
		case cocos2d::EventKeyboard::KeyCode::KEY_HOME:
			GameUtil::toHomeScene();
			break;
		default:
			break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}