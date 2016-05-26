#include "GameScene.h"
#include "LayoutUtil.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* GameScene::createScene() {
    auto layer = GameScene::create();
    auto scene = Scene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init() {
    if (!Layer::init()) {
        return false;
    }

    return true;
}
