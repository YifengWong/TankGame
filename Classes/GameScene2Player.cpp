#include "GameScene2Player.h"
#include "GameConfig.h"
#include "EnemyNormalSprite.h"
#include "EnemyBossSprite.h"
#include "GameUtil.h"

USING_NS_CC;
using namespace cocos2d::ui;

PlayerDualSprite* GameScene2Player::player_1 = nullptr;
PlayerDualSprite* GameScene2Player::player_2 = nullptr;

PlayerDualSprite* GameScene2Player::getPlayer_1() {
	return player_1;
}
PlayerDualSprite* GameScene2Player::getPlayer_2() {
	return player_2;
}

Scene* GameScene2Player::createScene() {
	// Create a scene with a physics world
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Point(0, 0));
	scene->getPhysicsWorld()->setDebugDrawMask(
		GameConfig::DRAW_WORLD_EDGE ? PhysicsWorld::DEBUGDRAW_ALL : PhysicsWorld::DEBUGDRAW_NONE);

	auto layer = GameScene2Player::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene2Player::init() {
	if (!Layer::init()) {
		return false;
	}

	// Add sprites
	addBackground();
	addBoundary();
	addPlayer();
	addWalls();

	// Add event listeners
	addKeyboardListener();
	addContactListener();

	// Set schedule
	schedule(schedule_selector(GameScene2Player::update));

	return true;
}

void GameScene2Player::update(float f) {
}

void GameScene2Player::addBackground() {
	auto visibleSize = GameUtil::getVisibleSize();
	auto bgsprite = Sprite::create("background.png");
	bgsprite->setPosition(GameUtil::getPosition(GameUtil::PositionType::CENTER));
	bgsprite->setScale(visibleSize.width / bgsprite->getContentSize().width, \
		visibleSize.height / bgsprite->getContentSize().height);
	addChild(bgsprite);
}

void GameScene2Player::addBoundary() {
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

void GameScene2Player::addPlayer() {
	player_1 = PlayerDualSprite::create(PlayerDualSprite::PLAYER_1);
	player_1->setPosition(GameUtil::getPosition(GameUtil::PositionType::LEFT_BOTTOM));
	addChild(player_1);

	player_2 = PlayerDualSprite::create(PlayerDualSprite::PLAYER_2);
	player_2->setPosition(GameUtil::getPosition(GameUtil::PositionType::RIGHT_TOP));
	addChild(player_2);
}

void GameScene2Player::addEnemies() {
	//May be for get more points?
}

void GameScene2Player::addWalls() {
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

void GameScene2Player::addKeyboardListener() {
	auto keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event) {
		if (player_1 && player_2) {
			switch (code) {
			case cocos2d::EventKeyboard::KeyCode::KEY_A:
				player_1->setMoveVal(Direction::LEFT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_D:
				player_1->setMoveVal(Direction::RIGHT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_W:
				player_1->setMoveVal(Direction::UP);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_S:
				player_1->setMoveVal(Direction::DOWN);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				player_2->setMoveVal(Direction::LEFT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				player_2->setMoveVal(Direction::RIGHT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
				player_2->setMoveVal(Direction::UP);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				player_2->setMoveVal(Direction::DOWN);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
				player_1->fire(this);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
				player_2->fire(this);
				break;
			default:
				break;
			}
		}
	};

	keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event* event) {
		if (player_1) {
			switch (code) {
			case cocos2d::EventKeyboard::KeyCode::KEY_A:
				player_1->resetMoveVal(Direction::LEFT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_D:
				player_1->resetMoveVal(Direction::RIGHT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_W:
				player_1->resetMoveVal(Direction::UP);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_S:
				player_1->resetMoveVal(Direction::DOWN);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				player_2->resetMoveVal(Direction::LEFT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				player_2->resetMoveVal(Direction::RIGHT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
				player_2->resetMoveVal(Direction::UP);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				player_2->resetMoveVal(Direction::DOWN);
				break;
			default:
				break;
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void GameScene2Player::addMouseListener() {
	auto mouseListener = EventListenerMouse::create();

	mouseListener->onMouseUp = [&](EventMouse *event) {
		// getLocationInView() returns openGL coordinate,
		// not screen coordiante, maybe this is a bug.
		if (player_1 && event->getMouseButton() == MouseButton::Left
			&& PlayerBulletSprite::getBulletCount() < GameConfig::PLAYER_BULLET_NUM_LIMIT) {
			Vec2 target = event->getLocationInView();
			//player_1->fire(this, target);
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void GameScene2Player::addContactListener() {
	auto contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactSeparate = [&](PhysicsContact &contact) {
		auto body1 = contact.getShapeA()->getBody();
		auto body2 = contact.getShapeB()->getBody();
		if (body1 && body2) {
			// Player hits enemy
			if (body1->getTag() == GameConfig::PLAYER_TAG
				&& body2->getTag() == GameConfig::ENEMY_TAG) {
				meetPlayerWithEnemy(dynamic_cast<PlayerDualSprite*>(body1->getNode()),
					dynamic_cast<EnemySpriteBase*>(body2->getNode()));
			} else if (body1->getTag() == GameConfig::ENEMY_TAG
				&& body2->getTag() == GameConfig::PLAYER_TAG) {
				meetPlayerWithEnemy(dynamic_cast<PlayerDualSprite*>(body2->getNode()),
					dynamic_cast<EnemySpriteBase*>(body1->getNode()));
			}

			// Player hits enemy bullet
			if (body1->getTag() == GameConfig::PLAYER_TAG
				&& body2->getTag() == GameConfig::BULLET_ENEMY_TAG) {
				meetPlayerWithEnemyBullet(dynamic_cast<PlayerDualSprite*>(body1->getNode()),
					dynamic_cast<EnemyBulletSprite*>(body2->getNode()));
			} else if (body1->getTag() == GameConfig::BULLET_ENEMY_TAG
				&& body2->getTag() == GameConfig::PLAYER_TAG) {
				meetPlayerWithEnemyBullet(dynamic_cast<PlayerDualSprite*>(body2->getNode()),
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
				meetPlayerWithWall(dynamic_cast<PlayerDualSprite*>(body1->getNode()),
					dynamic_cast<WallSprite*>(body2->getNode()));
			} else if (body1->getTag() == GameConfig::WALL_TAG
				&& body2->getTag() == GameConfig::PLAYER_TAG) {
				meetPlayerWithWall(dynamic_cast<PlayerDualSprite*>(body2->getNode()),
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


void GameScene2Player::meetPlayerWithEnemy(PlayerDualSprite *plyr, EnemySpriteBase *enemy) {
	if (plyr) {
		if (GameUtil::isNormalEnemy(enemy)) {
			plyr->decreaseHP(GameConfig::ENEMY_NORMAL_COLLISION_DAMAGE);
		} else if (GameUtil::isBossEnemy(enemy)) {
			plyr->decreaseHP(GameConfig::ENEMY_BOSS_COLLISION_DAMAGE);
		}
		log("Player HP: %d", plyr->getHP()->getValue());
		if (plyr->isDead()) {
			plyr->removeFromParent();
			GameScene2Player::player_1 = nullptr;
		}
	}
}

void GameScene2Player::meetPlayerWithEnemyBullet(PlayerDualSprite *plyr, EnemyBulletSprite *enemyBullet) {
	if (plyr) {
		plyr->decreaseHP(GameConfig::BULLET_DAMAGE);
		log("Player HP: %d", plyr->getHP()->getValue());
		if (plyr->isDead()) {
			plyr->removeFromParent();
			GameScene2Player::player_1 = nullptr;
		}
	}

	if (enemyBullet) {
		enemyBullet->removeFromParent();
		enemyBullet = nullptr;
	}
}

void GameScene2Player::meetEnemyWithPlayerBullet(EnemySpriteBase *enemy, PlayerBulletSprite *playerBullet) {
	if (playerBullet) {
		playerBullet->removeFromParent();
		playerBullet = nullptr;
	}

	if (enemy) {
		enemy->decreaseHP(GameConfig::BULLET_DAMAGE);
		log("Enemy HP: %d", enemy->getHP()->getValue());
		if (enemy->isDead()) {
			enemy->removeFromParent();
			enemy = nullptr;
		}
	}
}

void GameScene2Player::meetPlayerWithWall(PlayerDualSprite *plyr, WallSprite *wall) {
	if (plyr) {
		plyr->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
}

void GameScene2Player::meetEnemyWithWall(EnemySpriteBase *enemy, WallSprite *wall) {
	if (enemy) {
		enemy->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
}

void GameScene2Player::meetPlayerBulletWithWall(PlayerBulletSprite *playerBullet, WallSprite *wall) {
	if (wall && wall->isBreakable()) {
		wall->removeFromParent();
		if (playerBullet) {
			playerBullet->removeFromParent();
		}
	}
}

void GameScene2Player::meetEnemyBulletWithWall(EnemyBulletSprite *enemyBullet, WallSprite *wall) {
	if (wall && wall->isBreakable()) {
		wall->removeFromParent();
		if (enemyBullet) {
			enemyBullet->removeFromParent();
		}
	}
}

