#include "GameScene1Player.h"
#include "GameConfig.h"
#include "EnemyNormalSprite.h"
#include "EnemyBossSprite.h"
#include "GameUtil.h"
#include "HomeScene.h"
#include "GameScriptFactory.h"

USING_NS_CC;
using namespace cocos2d::ui;

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

#if (TEST_GETPOSITION == true)
    for (unsigned i = 0; i < GameConfig::WINDOW_ROW_NUM; ++i) {
        for (unsigned j = 0; j < GameConfig::WINDOW_COLUMN_NUM; ++j) {
            auto pos = GameUtil::getPosition(i, j);
            auto tmp = EnemyNormalSprite::create();
            tmp->setPosition(pos);
            addChild(tmp);
        }
    }
    return true;
#endif

    // Checkpoints loaded failed
    if (GameScriptFactory::getInstance()->getStageCount() == 0) {
        return true;
    }

    // Add sprites
    addBackground();
    addBoundary();
    addPlayer();
    addEnemies();
    addWalls();
    addGameInfo();

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

void GameScene1Player::addGameInfo() {
    winBtn = Button::create();
    winBtn->setTitleText("YOU WIN");
    winBtn->setTitleFontSize(30);
    winBtn->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER));
    winBtn->addClickEventListener([](Ref* pSender) {
        GameUtil::toHomeScene();
    });
    winBtn->setVisible(false);
    addChild(winBtn, 1);

    gameoverBtn = Button::create();
    gameoverBtn->setTitleText("GAME OVER");
    gameoverBtn->setTitleFontSize(30);
    gameoverBtn->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER));
    gameoverBtn->addClickEventListener([](Ref* pSender) {
        GameUtil::toHomeScene();
    });
    gameoverBtn->setVisible(false);
    addChild(gameoverBtn, 1);

    nextBtn = Button::create();
    nextBtn->setTitleText("NEXT");
    nextBtn->setTitleFontSize(30);
    nextBtn->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER));
    nextBtn->addClickEventListener([&](Ref* pSender) {
        if (GameUtil::hasNextCheckpoint()) {
            GameUtil::toNextCheckpoint();
        }
    });
    nextBtn->setVisible(false);
    addChild(nextBtn, 1);
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
    auto stage = GameScriptFactory::getInstance()->getStages()->at(GameConfig::CURRENT_STAGE);
    auto pos = GameUtil::getPosition(stage.player1Row, stage.player1Col);
    player = PlayerSingleSprite::create(this);
    player->setPosition(pos);
    addChild(player);
}

void GameScene1Player::addEnemies() {
    auto stage = GameScriptFactory::getInstance()->getStages()->at(GameConfig::CURRENT_STAGE);
    auto enemies = stage.enemies;

    for (const auto &e : enemies) {
        EnemySpriteBase *enemy = nullptr;
        switch (e.type) {
            case GameScriptFactory::EnemyType::NORMAL:
                enemy = EnemyNormalSprite::create(this);
                break;
            case GameScriptFactory::EnemyType::BOSS:
                enemy = EnemyBossSprite::create(this);
                break;
            default:
                break;
        }

        if (enemy) {
            auto pos = GameUtil::getPosition(e.enemyRow, e.enemyCol);
            enemy->setPosition(pos);
            addChild(enemy);
            ++enemyCnt;
        }
    }
}

void GameScene1Player::addWalls() {
    auto stage = GameScriptFactory::getInstance()->getStages()->at(GameConfig::CURRENT_STAGE);
    auto walls = stage.walls;

    for (const auto &w : walls) {
        auto wall = WallSprite::create(w.breakable);
        auto pos = GameUtil::getPosition(w.wallRow, w.wallCol);
        wall->setPosition(pos);
        addChild(wall);
    }
}

void GameScene1Player::addKeyboardListener() {
    auto keyboardListener = EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event) {
        switch (code) {
            case cocos2d::EventKeyboard::KeyCode::KEY_A:
                if (!GameScene1Player::player) return;
                player->setMoveVal(GameUtil::Direction::LEFT);
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_D:
                if (!GameScene1Player::player) return;
                player->setMoveVal(GameUtil::Direction::RIGHT);
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_W:
                if (!GameScene1Player::player) return;
                player->setMoveVal(GameUtil::Direction::UP);
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_S:
                if (!GameScene1Player::player) return;
                player->setMoveVal(GameUtil::Direction::DOWN);
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_HOME:
                GameUtil::toHomeScene();
                break;
            default:
                break;
        }
    };

    keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event* event) {
        if (player) {
            switch (code) {
                case cocos2d::EventKeyboard::KeyCode::KEY_A:
                    player->resetMoveVal(GameUtil::Direction::LEFT);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_D:
                    player->resetMoveVal(GameUtil::Direction::RIGHT);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_W:
                    player->resetMoveVal(GameUtil::Direction::UP);
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_S:
                    player->resetMoveVal(GameUtil::Direction::DOWN);
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
                meetBulletWithWall(dynamic_cast<BulletSpriteBase*>(body1->getNode()),
                                   dynamic_cast<WallSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::WALL_TAG
                       && body2->getTag() == GameConfig::BULLET_PLAYER_TAG) {
                meetBulletWithWall(dynamic_cast<BulletSpriteBase*>(body2->getNode()),
                                   dynamic_cast<WallSprite*>(body1->getNode()));
            }

            // Enemy bullet hits the wall
            if (body1->getTag() == GameConfig::BULLET_ENEMY_TAG
                && body2->getTag() == GameConfig::WALL_TAG) {
                meetBulletWithWall(dynamic_cast<BulletSpriteBase*>(body1->getNode()),
                                   dynamic_cast<WallSprite*>(body2->getNode()));
            } else if (body1->getTag() == GameConfig::WALL_TAG
                       && body2->getTag() == GameConfig::BULLET_ENEMY_TAG) {
                meetBulletWithWall(dynamic_cast<BulletSpriteBase*>(body2->getNode()),
                                   dynamic_cast<WallSprite*>(body1->getNode()));
            }
        }
    };

    _eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);
}


void GameScene1Player::meetPlayerWithEnemy(PlayerSingleSprite *plyr, EnemySpriteBase *enemy) {
    if (plyr) {
        if (GameUtil::isNormalEnemy(enemy)) {
            plyr->decreaseHP(GameConfig::ENEMY_NORMAL_COLLISION_DAMAGE);
        } else if (GameUtil::isBossEnemy(enemy)) {
            plyr->decreaseHP(GameConfig::ENEMY_BOSS_COLLISION_DAMAGE);
        }
        log("Player HP: %d", plyr->getHP()->getValue());
        if (plyr->isDead()) {
            GameUtil::addParticles(this, plyr->getPosition(), GameUtil::ParticleType::EXPLODE);
            plyr->removeFromParent();
            GameScene1Player::player = nullptr;
        }
    }
}

void GameScene1Player::meetPlayerWithEnemyBullet(PlayerSingleSprite *plyr, EnemyBulletSprite *enemyBullet) {
    if (plyr) {
        plyr->decreaseHP(GameConfig::BULLET_DAMAGE);
        log("Player HP: %d", plyr->getHP()->getValue());
        if (plyr->isDead()) {
            GameUtil::addParticles(this, plyr->getPosition(), GameUtil::ParticleType::EXPLODE);
            plyr->removeFromParent();
            GameScene1Player::player = nullptr;
        }
    }

    if (enemyBullet) {
        enemyBullet->removeFromParent();
        GameUtil::playEffect(GameUtil::MusicEffectType::BULLET_HIT);
    }
}

void GameScene1Player::meetEnemyWithPlayerBullet(EnemySpriteBase *enemy, PlayerBulletSprite *playerBullet) {
    if (playerBullet) {
        playerBullet->removeFromParent();
        GameUtil::playEffect(GameUtil::MusicEffectType::BULLET_HIT);
    }

    if (enemy) {
        enemy->decreaseHP(GameConfig::BULLET_DAMAGE);
        log("Enemy HP: %d", enemy->getHP()->getValue());
        if (enemy->isDead()) {
            GameUtil::addParticles(this, enemy->getPosition(), GameUtil::ParticleType::EXPLODE);
			
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

void GameScene1Player::meetBulletWithWall(BulletSpriteBase *bullet, WallSprite *wall) {
    if (wall && wall->isBreakable()) {
        wall->removeFromParent();
        if (bullet) {
            bullet->removeFromParent();
            GameUtil::playEffect(GameUtil::MusicEffectType::BULLET_HIT);
        }
    }
}

const PlayerSingleSprite* GameScene1Player::getPlayer() const {
    return player;
}

void GameScene1Player::showGameoverBtn() {
    if (isOneInfoShown()) return;
    gameoverBtn->setVisible(true);
}

void GameScene1Player::showNextBtn() {
    if (isOneInfoShown()) return;
    nextBtn->setVisible(true);
}

void GameScene1Player::showWinBtn() {
    if (isOneInfoShown()) return;
    winBtn->setVisible(true);
}

void GameScene1Player::decreaseEnemyCnt() {
    if (enemyCnt > 0) {
        --enemyCnt;
        if (enemyCnt == 0) {
            if (GameUtil::hasNextCheckpoint()) {
                showNextBtn();
            } else {
                showWinBtn();
            }
        }
    }
}

bool GameScene1Player::isOneInfoShown() const {
    return gameoverBtn->isVisible() || nextBtn->isVisible() || winBtn->isVisible();
}
