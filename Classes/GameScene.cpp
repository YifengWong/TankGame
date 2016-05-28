#include "GameScene.h"
#include "Constants.h"
#include "WallSprite.h"

USING_NS_CC;
using namespace cocos2d::ui;

PlayerSprite* GameScene::player = nullptr;

PlayerSprite* GameScene::getPlayer() {
    return player;
}

Scene* GameScene::createScene() {
    // Create a scene with a physics world
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Point(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(
        Constants::DRAW_WORLD_EDGE ? PhysicsWorld::DEBUGDRAW_ALL : PhysicsWorld::DEBUGDRAW_NONE);

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
    addEnemey();
    addWall();

    // Add event listeners
    addKeyboardListener();
    addContactListener();
    addMouseListener();

    // Set schedule
    schedule(schedule_selector(GameScene::update));

    return true;
}

void GameScene::update(float f) {
}

void GameScene::addBoundary() {
    // Create physicsBody
    // Customize PhysicsMaterial to enable mirror reflection
    auto physicBody = PhysicsBody::createEdgeBox(LayoutUtil::getVisibleSize(),
                                                 PhysicsMaterial(0, 2, 0));
    physicBody->setDynamic(false);
    // Set bitmasks
    physicBody->setGroup(Constants::WALL_PHYSIC_GROUP);
    physicBody->setCategoryBitmask(Constants::WALL_PHYSIC_CATEGORY_BM);
    physicBody->setCollisionBitmask(Constants::WALL_PHYSIC_COLLISION_BM);
    physicBody->setContactTestBitmask(Constants::WALL_PHYSIC_CONTACT_BM);
    physicBody->setTag(Constants::WALL_TAG);
    // Create sprite
    auto boudary = Sprite::create();
    boudary->setPosition(LayoutUtil::getPosition(LayoutUtil::PositionType::CENTER));
    boudary->setPhysicsBody(physicBody);
    // Add to layer
    addChild(boudary);
}

void GameScene::addPlayer() {
    player = PlayerSprite::create();
    player->setPosition(LayoutUtil::getPosition(LayoutUtil::PositionType::LEFT_BOTTOM));
    addChild(player);
}

void GameScene::addEnemey() {
    auto enemy1 = EnemySprite::create(this);
    enemy1->setPosition(LayoutUtil::getPosition(LayoutUtil::PositionType::RIGHT_BOTTOM));
    addChild(enemy1);

    auto enemy2 = EnemySprite::create(this);
    enemy2->setPosition(LayoutUtil::getPosition(LayoutUtil::PositionType::LEFT_TOP));
    addChild(enemy2);

    auto enemy3 = EnemySprite::create(this);
    enemy3->setPosition(LayoutUtil::getPosition(LayoutUtil::PositionType::RIGHT_TOP));
    addChild(enemy3);
}

void GameScene::addWall() {
    auto wall1 = WallSprite::create();
    wall1->setPosition(LayoutUtil::getPosition(LayoutUtil::PositionType::CENTER));
    addChild(wall1);
}

void GameScene::addKeyboardListener() {
    auto keyboardListener = EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event) {
        if (player) {
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
        if (player) {
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

void GameScene::addMouseListener() {
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseUp = [&](EventMouse *event) {
        // getLocationInView() returns openGL coordinate,
        // not screen coordiante, maybe this is a bug.
        if (player && event->getMouseButton() == MouseButton::Left
            && PlayerBulletSprite::getBulletCount() < Constants::PLAYER_BULLET_NUM_LIMIT) {
            Vec2 target = event->getLocationInView();
            player->fire(this, target);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void GameScene::addContactListener() {
    auto contactListener = EventListenerPhysicsContact::create();

    contactListener->onContactSeparate = [&](PhysicsContact &contact) {
        auto body1 = contact.getShapeA()->getBody();
        auto body2 = contact.getShapeB()->getBody();
        if (body1 && body2) {
            // Player hits enemy
            if (body1->getTag() == Constants::PLAYER_TAG
                && body2->getTag() == Constants::ENEMY_TAG) {
                meetPlayerWithEnemy(static_cast<EnemySprite*>(body2->getNode()));
            } else if (body1->getTag() == Constants::ENEMY_TAG
                       && body2->getTag() == Constants::PLAYER_TAG) {
                meetPlayerWithEnemy(static_cast<EnemySprite*>(body1->getNode()));
            }

            // Player hits enemy bullet
            if (body1->getTag() == Constants::PLAYER_TAG
                && body2->getTag() == Constants::BULLET_ENEMY_TAG) {
                meetPlayerWithEnemyBullet(static_cast<EnemyBulletSprite*>(body2->getNode()));
            } else if (body1->getTag() == Constants::BULLET_ENEMY_TAG
                       && body2->getTag() == Constants::PLAYER_TAG) {
                meetPlayerWithEnemyBullet(static_cast<EnemyBulletSprite*>(body1->getNode()));
            }

            // Enemy hits player bullet
            if (body1->getTag() == Constants::ENEMY_TAG
                && body2->getTag() == Constants::BULLET_PLAYER_TAG) {
                meetEnemyWithPlayerBullet(static_cast<EnemySprite*>(body1->getNode()),
                                          static_cast<PlayerBulletSprite*>(body2->getNode()));
            } else if (body1->getTag() == Constants::BULLET_PLAYER_TAG
                       && body2->getTag() == Constants::ENEMY_TAG) {
                meetEnemyWithPlayerBullet(static_cast<EnemySprite*>(body2->getNode()),
                                          static_cast<PlayerBulletSprite*>(body1->getNode()));
            }

            // Player hits the wall
            if (body1->getTag() == Constants::PLAYER_TAG
                && body2->getTag() == Constants::WALL_TAG) {
                meetPlayerWithWall(static_cast<PlayerSprite*>(body1->getNode()));
            } else if (body1->getTag() == Constants::WALL_TAG
                       && body2->getTag() == Constants::PLAYER_TAG) {
                meetPlayerWithWall(static_cast<PlayerSprite*>(body2->getNode()));
            }

            // Enemy hits the wall
            if (body1->getTag() == Constants::ENEMY_TAG
                && body2->getTag() == Constants::WALL_TAG) {
                meetEnemyWithWall(static_cast<EnemySprite*>(body1->getNode()));
            } else if (body1->getTag() == Constants::WALL_TAG
                       && body2->getTag() == Constants::ENEMY_TAG) {
                meetEnemyWithWall(static_cast<EnemySprite*>(body2->getNode()));
            }
        }
    };

    _eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);
}


void GameScene::meetPlayerWithEnemy(EnemySprite *enemy) {
    if (GameScene::player) {
        //GameScene::player->removeFromParent();
        //GameScene::player = nullptr;
    }
}

void GameScene::meetPlayerWithEnemyBullet(EnemyBulletSprite *enemyBullet) {
    if (GameScene::player) {
        //GameScene::player->removeFromParent();
        //GameScene::player = nullptr;
    }

    if (enemyBullet) {
        enemyBullet->removeFromParent();
        enemyBullet = nullptr;
    }
}

void GameScene::meetEnemyWithPlayerBullet(EnemySprite *enemy, PlayerBulletSprite *playerBullet) {
    if (playerBullet) {
        playerBullet->removeFromParent();
        playerBullet = nullptr;
    }

    if (enemy) {
        enemy->removeFromParent();
    }
}

void GameScene::meetPlayerWithWall(PlayerSprite *player) {
    if (GameScene::player) {
        GameScene::player->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }
}

void GameScene::meetEnemyWithWall(EnemySprite *enemy) {
    if (enemy) {
        enemy->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }
}
