#include "GameScene.h"
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
    addBoundary();
    addPlayer();

    // Add event listeners
    addKeyboardListener();
    addContactListener();

    // Set schedule
    schedule(schedule_selector(GameScene::update));

    return true;
}

void GameScene::update(float f) {
    if (player != NULL) {
        player->move();
    }
}

void GameScene::addBoundary() {
    // Create physicsBody
    auto physicBody = PhysicsBody::createEdgeBox(LayoutUtil::getVisibleSize());
    physicBody->setDynamic(false);
    physicBody->setTag(BOUNDARY_TAG);
    // Set bitmasks
    physicBody->setGroup(Constants::BOUND_PHYSIC_GROUP);
    physicBody->setCategoryBitmask(Constants::BOUND_PHYSIC_CATEGORY_BM);
    physicBody->setCollisionBitmask(Constants::BOUND_PHYSIC_COLLISION_BM);
    physicBody->setContactTestBitmask(Constants::BOUND_PHYSIC_CONTACT_BM);
    // Create sprite
    auto boudary = Sprite::create();
    boudary->setPosition(LayoutUtil::getCenterPosition());
    boudary->setPhysicsBody(physicBody);
    // Add to layer
    addChild(boudary);
}

void GameScene::addPlayer() {
    player = PlayerSprite::create();
    player->setPosition(LayoutUtil::getCenterPosition());
    player->getPhysicsBody()->setTag(PLAYER_TAG);
    addChild(player);
}

void GameScene::addKeyboardListener() {
    auto keyboardListener = EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event) {
        if (player != NULL) {
            switch (code) {
                case cocos2d::EventKeyboard::KeyCode::KEY_A:
                    player->setMoveVal(Direction::LEFT);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_D:
                    player->setMoveVal(Direction::RIGHT);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_W:
                    player->setMoveVal(Direction::UP);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_S:
                    player->setMoveVal(Direction::DOWN);
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
                    player->resetMoveVal(Direction::LEFT);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_D:
                    player->resetMoveVal(Direction::RIGHT);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_W:
                    player->resetMoveVal(Direction::UP);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_S:
                    player->resetMoveVal(Direction::DOWN);
                    break;
                default:
                    break;
            }
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void GameScene::addContactListener() {
    auto contactListener = EventListenerPhysicsContact::create();

    contactListener->onContactBegin = [](PhysicsContact& contact) {
        auto body1 = contact.getShapeA()->getBody();
        auto body2 = contact.getShapeB()->getBody();

        if (body1 && body2) {
            // TODO Contack listener
            log("onContactBegin() triggered.");
        }

        return true;
    };

    _eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);
}
