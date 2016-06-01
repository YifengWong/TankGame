#include "GameScene1Player.h"
#include "GameConfig.h"
#include "EnemyNormalSprite.h"
#include "EnemyBossSprite.h"
#include "GameUtil.h"

USING_NS_CC;
using namespace cocos2d::ui;

PlayerSingleSprite* GameScene1Player::player = nullptr;

PlayerSingleSprite* GameScene1Player::getPlayer() {
    return player;
}

Scene* GameScene1Player::createScene() {
    // Create a scene with a physics world
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Point(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(
        GameConfig::DRAW_WORLD_EDGE ? PhysicsWorld::DEBUGDRAW_ALL : PhysicsWorld::DEBUGDRAW_NONE);

    auto layer = GameScene1Player::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene1Player::init() {
    if (!Layer::init()) {
        return false;
    }

    // Add sprites
    addBackground();
    addBoundary();
    addPlayer();
    addEnemies();
    addWalls();

    // Add event listeners
    addKeyboardListener();
    addContactListener();
    addMouseListener();

    // Set schedule
    schedule(schedule_selector(GameScene1Player::update));

    return true;
}

void GameScene1Player::update(float f) {
}

void GameScene1Player::addBackground() {
    auto visibleSize = GameUtil::getVisibleSize();
    auto bgsprite = Sprite::create("background.png");
    bgsprite->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER));
    bgsprite->setScale(visibleSize.width / bgsprite->getContentSize().width, \
                       visibleSize.height / bgsprite->getContentSize().height);
    addChild(bgsprite);
}

void GameScene1Player::addBoundary() {
    // Create physicsBody
    // Customize PhysicsMaterial to enable mirror reflection
    auto physicBody = PhysicsBody::createEdgeBox(GameUtil::getVisibleSize(),
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
    boudary->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER));
    boudary->setPhysicsBody(physicBody);
    // Add to layer
    addChild(boudary);
}

void GameScene1Player::addPlayer() {
    player = PlayerSingleSprite::create();
    player->setPosition(GameUtil::getPosition(GameUtil::PositionType::LEFT_BOTTOM));
    addChild(player);
}

void GameScene1Player::addEnemies() {
    auto enemyNormal = EnemyNormalSprite::create(this);
    enemyNormal->setPosition(GameUtil::getPosition(GameUtil::PositionType::LEFT_TOP));
    addChild(enemyNormal);

    auto enemyBoss = EnemyBossSprite::create(this);
    enemyBoss->setPosition(GameUtil::getPosition(GameUtil::PositionType::RIGHT_TOP));
    addChild(enemyBoss);

    enemyNormal = EnemyNormalSprite::create(this);
    enemyNormal->setPosition(GameUtil::getPosition(GameUtil::PositionType::RIGHT_BOTTOM));
    addChild(enemyNormal);
}

void GameScene1Player::addWalls() {
    auto wall = WallSprite::create(true);
    wall->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER_LEFT));
    addChild(wall);

    wall = WallSprite::create(true);
    wall->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER_TOP));
    addChild(wall);

    wall = WallSprite::create(true);
    wall->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER_RIGHT));
    addChild(wall);

    wall = WallSprite::create(true);
    wall->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER_DOWN));
    addChild(wall);

    wall = WallSprite::create(false);
    wall->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER));
    addChild(wall);

    wall = WallSprite::create(false);
    wall->setPosition(GameUtil::getPosition(GameUtil::PositionType::EDGE_CENTER_BOTTOM));
    addChild(wall);

    wall = WallSprite::create(false);
    wall->setPosition(GameUtil::getPosition(GameUtil::PositionType::EDGE_CENTER_LEFT));
    addChild(wall);

    wall = WallSprite::create(false);
    wall->setPosition(GameUtil::getPosition(GameUtil::PositionType::EDGE_CENTER_RIGHT));
    addChild(wall);

    wall = WallSprite::create(false);
    wall->setPosition(GameUtil::getPosition(GameUtil::PositionType::EDGE_CENTER_TOP));
    addChild(wall);
}

void GameScene1Player::addKeyboardListener() {
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

void GameScene1Player::addMouseListener() {
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseUp = [&](EventMouse *event) {
        // getLocationInView() returns openGL coordinate,
        // not screen coordiante, maybe this is a bug.
        if (player && event->getMouseButton() == MouseButton::Left
            && PlayerBulletSprite::getBulletCount() < GameConfig::PLAYER_BULLET_NUM_LIMIT) {
            Vec2 target = event->getLocationInView();
            player->fire(this, &target);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void GameScene1Player::addContactListener() {
    auto contactListener = EventListenerPhysicsContact::create();

    contactListener->onContactSeparate = [&](PhysicsContact &contact) {
        auto body1 = contact.getShapeA()->getBody();
        auto body2 = contact.getShapeB()->getBody();
        if (body1 && body2) {
            // Player hits enemy
            if (body1->getTag() == GameConfig::PLAYER_TAG
                && body2->getTag() == GameConfig::ENEMY_TAG) {
                meetPlayerWithEnemy(dynamic_cast<PlayerSingleSprite*>(body1->getNode()),
                                    dynamic_cast<EnemySpriteBase*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::ENEMY_TAG
                       && body2->getTag() == GameConfig::PLAYER_TAG) {
                meetPlayerWithEnemy(dynamic_cast<PlayerSingleSprite*>(body2->getNode()),
                                    dynamic_cast<EnemySpriteBase*>(body1->getNode()));
            }

            // Player hits enemy bullet
            if (body1->getTag() == GameConfig::PLAYER_TAG
                && body2->getTag() == GameConfig::BULLET_ENEMY_TAG) {
                meetPlayerWithEnemyBullet(dynamic_cast<PlayerSingleSprite*>(body1->getNode()),
                                          dynamic_cast<EnemyBulletSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::BULLET_ENEMY_TAG
                       && body2->getTag() == GameConfig::PLAYER_TAG) {
                meetPlayerWithEnemyBullet(dynamic_cast<PlayerSingleSprite*>(body2->getNode()),
                                          dynamic_cast<EnemyBulletSprite*>(body1->getNode()));
            }

            // Enemy hits player bullet
            if (body1->getTag() == GameConfig::ENEMY_TAG
                && body2->getTag() == GameConfig::BULLET_PLAYER_TAG) {
                meetEnemyWithPlayerBullet(dynamic_cast<EnemySpriteBase*>(body1->getNode()),
                                          dynamic_cast<PlayerBulletSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::BULLET_PLAYER_TAG
                       && body2->getTag() == GameConfig::ENEMY_TAG) {
                meetEnemyWithPlayerBullet(dynamic_cast<EnemySpriteBase*>(body2->getNode()),
                                          dynamic_cast<PlayerBulletSprite*>(body1->getNode()));
            }

            // Player hits the wall
            if (body1->getTag() == GameConfig::PLAYER_TAG
                && body2->getTag() == GameConfig::WALL_TAG) {
                meetPlayerWithWall(dynamic_cast<PlayerSingleSprite*>(body1->getNode()),
                                   dynamic_cast<WallSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::WALL_TAG
                       && body2->getTag() == GameConfig::PLAYER_TAG) {
                meetPlayerWithWall(dynamic_cast<PlayerSingleSprite*>(body2->getNode()),
                                   dynamic_cast<WallSprite*>(body1->getNode()));
            }

            // Enemy hits the wall
            if (body1->getTag() == GameConfig::ENEMY_TAG
                && body2->getTag() == GameConfig::WALL_TAG) {
                meetEnemyWithWall(dynamic_cast<EnemySpriteBase*>(body1->getNode()),
                                  dynamic_cast<WallSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::WALL_TAG
                       && body2->getTag() == GameConfig::ENEMY_TAG) {
                meetEnemyWithWall(dynamic_cast<EnemySpriteBase*>(body2->getNode()),
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


void GameScene1Player::meetPlayerWithEnemy(PlayerSingleSprite *plyr, EnemySpriteBase *enemy) {
    if (plyr) {
        if (GameUtil::isNormalEnemy(enemy)) {
            plyr->getHP()->decrease(GameConfig::ENEMY_NORMAL_COLLISION_DAMAGE);
        } else if (GameUtil::isBossEnemy(enemy)) {
            plyr->getHP()->decrease(GameConfig::ENEMY_BOSS_COLLISION_DAMAGE);
        }
        log("Player HP: %d", plyr->getHP()->getValue());
        if (plyr->isDead()) {
            plyr->removeFromParent();
            GameScene1Player::player = nullptr;
        }
    }
}

void GameScene1Player::meetPlayerWithEnemyBullet(PlayerSingleSprite *plyr, EnemyBulletSprite *enemyBullet) {
    if (plyr) {
        plyr->getHP()->decrease(GameConfig::BULLET_DAMAGE);
        log("Player HP: %d", plyr->getHP()->getValue());
        if (plyr->isDead()) {
            plyr->removeFromParent();
            GameScene1Player::player = nullptr;
        }
    }

    if (enemyBullet) {
        enemyBullet->removeFromParent();
    }
}

void GameScene1Player::meetEnemyWithPlayerBullet(EnemySpriteBase *enemy, PlayerBulletSprite *playerBullet) {
    if (playerBullet) {
        playerBullet->removeFromParent();
    }

    if (enemy) {
        enemy->getHP()->decrease(GameConfig::BULLET_DAMAGE);
        log("Enemy HP: %d", enemy->getHP()->getValue());
        if (enemy->isDead()) {
            enemy->removeFromParent();
        }
    }
}

void GameScene1Player::meetPlayerWithWall(PlayerSingleSprite *plyr, WallSprite *wall) {
    if (plyr) {
        plyr->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }
}

void GameScene1Player::meetEnemyWithWall(EnemySpriteBase *enemy, WallSprite *wall) {
    if (enemy) {
        auto curVel = enemy->getPhysicsBody()->getVelocity();
        curVel.normalize();
        if (GameUtil::isNormalEnemy(enemy)) {
            enemy->getPhysicsBody()->setVelocity(curVel * GameConfig::ENEMY_NORMAL_MOVE_SPEED);
        } else if (GameUtil::isBossEnemy(enemy)) {
            enemy->getPhysicsBody()->setVelocity(curVel * GameConfig::ENEMY_BOSS_MOVE_SPEED);
        }
    }
}

void GameScene1Player::meetPlayerBulletWithWall(PlayerBulletSprite *playerBullet, WallSprite *wall) {
    if (wall && wall->isBreakable()) {
        wall->removeFromParent();
        if (playerBullet) {
            playerBullet->removeFromParent();
        }
    }
}

void GameScene1Player::meetEnemyBulletWithWall(EnemyBulletSprite *enemyBullet, WallSprite *wall) {
    if (wall && wall->isBreakable()) {
        wall->removeFromParent();
        if (enemyBullet) {
            enemyBullet->removeFromParent();
        }
    }
}

