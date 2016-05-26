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

    // Add sprites
    addEdge();
    addPlayer();

    // Add event listeners
    addKeyboardListener();

    // Set schedule
    schedule(schedule_selector(GameScene::update));

    return true;
}

void GameScene::update(float f) {

}

void GameScene::addEdge() {
    // Create physicsBody
    auto physicBody = PhysicsBody::createEdgeBox(LayoutUtil::getVisibleSize());
    physicBody->setDynamic(false);
    // Set bitmasks
    physicBody->setGroup(Constants::EDGE_PHYSIC_GROUP);
    physicBody->setCategoryBitmask(Constants::EDGE_PHYSIC_CATEGORY_BM);
    physicBody->setContactTestBitmask(Constants::EDGE_PHYSIC_CONTACT_BM);
    // Create sprite
    auto edge = Sprite::create();
    edge->setPosition(LayoutUtil::getCenterPosition());
    edge->setPhysicsBody(physicBody);
    // Add to layer
    addChild(edge);
}

void GameScene::addPlayer() {
    player = PlayerSprite::create();
    player->setPosition(LayoutUtil::getCenterPosition());
    addChild(player);
}

void GameScene::addKeyboardListener() {
    auto keyboardListener = EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event) {
        if (player != NULL) {
            switch (code) {
                case cocos2d::EventKeyboard::KeyCode::KEY_A:
                    player->startMove(PlayerSprite::Direction::LEFT);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_D:
                    player->startMove(PlayerSprite::Direction::RIGHT);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_W:
                    player->startMove(PlayerSprite::Direction::UP);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_S:
                    player->startMove(PlayerSprite::Direction::DOWN);
                    break;
                default:
                    break;
            }
        }
    };

    keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event* event) {
        if (player != NULL) {
            switch (code) {
                case cocos2d::EventKeyboard::KeyCode::KEY_A:
                    player->stopMove(PlayerSprite::Direction::LEFT);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_D:
                    player->stopMove(PlayerSprite::Direction::RIGHT);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_W:
                    player->stopMove(PlayerSprite::Direction::UP);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_S:
                    player->stopMove(PlayerSprite::Direction::DOWN);
                    break;
                default:
                    break;
            }
        }
    };

    Director::getInstance()->getEventDispatcher()->
        addEventListenerWithSceneGraphPriority(keyboardListener, this);
}
