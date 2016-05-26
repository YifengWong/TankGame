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

}

void GameScene::addBoundary() {
    // Create physicsBody
    auto physicBody = PhysicsBody::createEdgeBox(LayoutUtil::getVisibleSize());
    physicBody->setDynamic(false);
    physicBody->setTag(BOUNDARY_TAG);
    // Set bitmasks
    physicBody->setGroup(Constants::BOUND_PHYSIC_GROUP);
    physicBody->setCategoryBitmask(Constants::BOUND_PHYSIC_CATEGORY_BM);
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

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void GameScene::addContactListener() {
    auto contactListener = EventListenerPhysicsContact::create();

    contactListener->onContactBegin = [](PhysicsContact& contact) {
        auto body1 = contact.getShapeA()->getBody();
        auto body2 = contact.getShapeB()->getBody();

        if (body1 && body2) {
            // When player hits the wall, stop the player
            if (body1->getTag() == PLAYER_TAG && body2->getTag() == BOUNDARY_TAG) {
                body1->setVelocity(Vec2(0, 0));
            } else if (body2->getTag() == PLAYER_TAG && body1->getTag() == BOUNDARY_TAG) {
                body2->setVelocity(Vec2(0, 0));
            }
        }

        return true;
    };

    _eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);
}
