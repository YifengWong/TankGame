#include "GameScene.h"
#include "LayoutUtil.h"
#include "Constants.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* GameScene::createScene() {
    // Create a scene with a physics world
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Point(0, 0));

    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init() {
    if (!Layer::init()) {
        return false;
    }

    addEdge();

    return true;
}

void GameScene::addEdge() {
    // Edge physicsBody
    auto body = PhysicsBody::createEdgeBox(LayoutUtil::getVisibleSize());
    body->setDynamic(false);

    // Edge sprite
    auto edge = Sprite::create();
    edge->setPosition(LayoutUtil::getCenterPosition());
    edge->setPhysicsBody(body);

    // Set bitmasks
    edge->getPhysicsBody()->setGroup(Constants::EDGE_PHYSIC_GROUP);
    edge->getPhysicsBody()->setCategoryBitmask(Constants::EDGE_PHYSIC_CATEGORY_BM);
    edge->getPhysicsBody()->setContactTestBitmask(Constants::EDGE_PHYSIC_CONTACT_BM);

    this->addChild(edge);
}
