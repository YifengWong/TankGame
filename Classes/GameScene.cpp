#include "GameScene.h"
#include "GameConfig.h"

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
        GameConfig::DRAW_WORLD_EDGE ? PhysicsWorld::DEBUGDRAW_ALL : PhysicsWorld::DEBUGDRAW_NONE);

    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init() {
    if (!Layer::init()) {
        return false;
    }

	addBackground();

    // Add sprites
    addBoundary();
    addPlayer();
    addEnemey();
	addBoss();
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
    physicBody->setGroup(GameConfig::WALL_PHYSIC_GROUP);
    physicBody->setCategoryBitmask(GameConfig::WALL_PHYSIC_CATEGORY_BM);
    physicBody->setCollisionBitmask(GameConfig::WALL_PHYSIC_COLLISION_BM);
    physicBody->setContactTestBitmask(GameConfig::WALL_PHYSIC_CONTACT_BM);
    physicBody->setTag(GameConfig::WALL_TAG);
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

void GameScene::addBoss() {
	auto boss = BossSprite::create(this);
	boss->setPosition(LayoutUtil::getPosition(LayoutUtil::PositionType::CENTER));
	addChild(boss);
}

void GameScene::addWall() {
    auto wall1 = WallSprite::create(true);
    wall1->setPosition(LayoutUtil::getPosition(LayoutUtil::PositionType::CENTER_LEFT));
    addChild(wall1);

    auto wall2 = WallSprite::create(true);
    wall2->setPosition(LayoutUtil::getPosition(LayoutUtil::PositionType::CENTER_TOP));
    addChild(wall2);

    auto wall3 = WallSprite::create(true);
    wall3->setPosition(LayoutUtil::getPosition(LayoutUtil::PositionType::CENTER_RIGHT));
    addChild(wall3);

    auto wall4 = WallSprite::create(true);
    wall4->setPosition(LayoutUtil::getPosition(LayoutUtil::PositionType::CENTER_DOWN));
    addChild(wall4);

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
            && PlayerBulletSprite::getBulletCount() < GameConfig::PLAYER_BULLET_NUM_LIMIT) {
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
            if (body1->getTag() == GameConfig::PLAYER_TAG
                && body2->getTag() == GameConfig::ENEMY_TAG) {
                meetPlayerWithEnemy(dynamic_cast<EnemySprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::ENEMY_TAG
                       && body2->getTag() == GameConfig::PLAYER_TAG) {
                meetPlayerWithEnemy(dynamic_cast<EnemySprite*>(body1->getNode()));
            }

            // Player hits enemy bullet
            if (body1->getTag() == GameConfig::PLAYER_TAG
                && body2->getTag() == GameConfig::BULLET_ENEMY_TAG) {
                meetPlayerWithEnemyBullet(dynamic_cast<EnemyBulletSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::BULLET_ENEMY_TAG
                       && body2->getTag() == GameConfig::PLAYER_TAG) {
                meetPlayerWithEnemyBullet(dynamic_cast<EnemyBulletSprite*>(body1->getNode()));
            }

            // Enemy hits player bullet
            if (body1->getTag() == GameConfig::ENEMY_TAG
                && body2->getTag() == GameConfig::BULLET_PLAYER_TAG) {
                meetEnemyWithPlayerBullet(dynamic_cast<EnemySprite*>(body1->getNode()),
                                          dynamic_cast<PlayerBulletSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::BULLET_PLAYER_TAG
                       && body2->getTag() == GameConfig::ENEMY_TAG) {
                meetEnemyWithPlayerBullet(dynamic_cast<EnemySprite*>(body2->getNode()),
                                          dynamic_cast<PlayerBulletSprite*>(body1->getNode()));
            }

            // Player hits the wall
            if (body1->getTag() == GameConfig::PLAYER_TAG
                && body2->getTag() == GameConfig::WALL_TAG) {
                meetPlayerWithWall(dynamic_cast<PlayerSprite*>(body1->getNode()),
                                   dynamic_cast<WallSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::WALL_TAG
                       && body2->getTag() == GameConfig::PLAYER_TAG) {
                meetPlayerWithWall(dynamic_cast<PlayerSprite*>(body2->getNode()),
                                   dynamic_cast<WallSprite*>(body1->getNode()));
            }

            // Enemy hits the wall
            if (body1->getTag() == GameConfig::ENEMY_TAG
                && body2->getTag() == GameConfig::WALL_TAG) {
                meetEnemyWithWall(dynamic_cast<EnemySprite*>(body1->getNode()),
                                  dynamic_cast<WallSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::WALL_TAG
                       && body2->getTag() == GameConfig::ENEMY_TAG) {
                meetEnemyWithWall(dynamic_cast<EnemySprite*>(body2->getNode()),
                                  dynamic_cast<WallSprite*>(body1->getNode()));
            }

            // Player bullet hits the wall
            if (body1->getTag() == GameConfig::BULLET_PLAYER_TAG
                && body2->getTag() == GameConfig::WALL_TAG) {
                meetPlayerBulletWithWall(dynamic_cast<PlayerBulletSprite*>(body1->getNode()),
                                         dynamic_cast<WallSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::WALL_TAG
                       && body2->getTag() == GameConfig::BULLET_PLAYER_TAG) {
                meetPlayerBulletWithWall(dynamic_cast<PlayerBulletSprite*>(body2->getNode()),
                                         dynamic_cast<WallSprite*>(body1->getNode()));
            }

            // Enemy bullet hits the wall
            if (body1->getTag() == GameConfig::BULLET_ENEMY_TAG
                && body2->getTag() == GameConfig::WALL_TAG) {
                meetEnemyBulletWithWall(dynamic_cast<EnemyBulletSprite*>(body1->getNode()),
                                        dynamic_cast<WallSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::WALL_TAG
                       && body2->getTag() == GameConfig::BULLET_ENEMY_TAG) {
                meetEnemyBulletWithWall(dynamic_cast<EnemyBulletSprite*>(body2->getNode()),
                                        dynamic_cast<WallSprite*>(body1->getNode()));
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
        //enemy->removeFromParent();
    }
}

void GameScene::meetPlayerWithWall(PlayerSprite *player, WallSprite *wall) {
    if (GameScene::player) {
        GameScene::player->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }
}

void GameScene::meetEnemyWithWall(EnemySprite *enemy, WallSprite *wall) {
    if (enemy) {
        enemy->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }
}

void GameScene::meetPlayerBulletWithWall(PlayerBulletSprite *playerBullet, WallSprite *wall) {
    if (wall && wall->isBreakable()) {
        wall->removeFromParent();
        if (playerBullet) {
            playerBullet->removeFromParent();
        }
    }
}

void GameScene::meetEnemyBulletWithWall(EnemyBulletSprite *enemyBullet, WallSprite *wall) {
    if (wall && wall->isBreakable()) {
        wall->removeFromParent();
        if (enemyBullet) {
            enemyBullet->removeFromParent();
        }
    }
}

void GameScene::addBackground() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto bgsprite = Sprite::create("background.png");
	bgsprite->setPosition(visibleSize / 2);
	bgsprite->setScale(visibleSize.width / bgsprite->getContentSize().width, \
		visibleSize.height / bgsprite->getContentSize().height);
	this->addChild(bgsprite, -1);
}
