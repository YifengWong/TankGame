#include "GameScene2Player.h"
#include "GameConfig.h"
#include "EnemyNormalSprite.h"
#include "EnemyBossSprite.h"
#include "GameUtil.h"

USING_NS_CC;
using namespace cocos2d::ui;

PlayerDualSprite* GameScene2Player::player_1 = nullptr;
PlayerDualSprite* GameScene2Player::player_2 = nullptr;

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
	//addBackground();
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
		switch (code) {
			case cocos2d::EventKeyboard::KeyCode::KEY_A:
                if (!player_1) return;
				player_1->setMoveVal(Direction::LEFT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_D:
                if (!player_1) return;
				player_1->setMoveVal(Direction::RIGHT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_W:
                if (!player_1) return;
				player_1->setMoveVal(Direction::UP);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_S:
                if (!player_1) return;
				player_1->setMoveVal(Direction::DOWN);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                if (!player_2) return;
				player_2->setMoveVal(Direction::LEFT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                if (!player_2) return;
				player_2->setMoveVal(Direction::RIGHT);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
                if (!player_2) return;
				player_2->setMoveVal(Direction::UP);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                if (!player_2) return;
				player_2->setMoveVal(Direction::DOWN);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
                if (!player_2) return;
				player_1->fire(this);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
                if (!player_2) return;
				player_2->fire(this);
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_HOME:
				GameUtil::returnToHome();
				break;
			default:
				break;
		}
	};

	keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event* event) {
		if (player_1 && player_2) {
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
					dynamic_cast<PlayerDualSprite*>(body2->getNode()));
			} else if (body1->getTag() == GameConfig::ENEMY_TAG
				&& body2->getTag() == GameConfig::PLAYER_TAG) {
				meetPlayerWithEnemy(dynamic_cast<PlayerDualSprite*>(body2->getNode()),
					dynamic_cast<PlayerDualSprite*>(body1->getNode()));
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
				meetEnemyWithPlayerBullet(dynamic_cast<PlayerDualSprite*>(body1->getNode()),
					dynamic_cast<PlayerBulletSprite*>(body2->getNode()));
			} else if (body1->getTag() == GameConfig::BULLET_PLAYER_TAG
				&& body2->getTag() == GameConfig::ENEMY_TAG) {
				meetEnemyWithPlayerBullet(dynamic_cast<PlayerDualSprite*>(body2->getNode()),
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
				meetEnemyWithWall(dynamic_cast<PlayerDualSprite*>(body1->getNode()),
					dynamic_cast<WallSprite*>(body2->getNode()));
			} else if (body1->getTag() == GameConfig::WALL_TAG
				&& body2->getTag() == GameConfig::ENEMY_TAG) {
				meetEnemyWithWall(dynamic_cast<PlayerDualSprite*>(body2->getNode()),
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


void GameScene2Player::meetPlayerWithEnemy(PlayerDualSprite *plyr, PlayerDualSprite *enemy) {
	if (plyr && enemy) {
		plyr->decreaseHP(GameConfig::ENEMY_NORMAL_COLLISION_DAMAGE);
		enemy->decreaseHP(GameConfig::ENEMY_NORMAL_COLLISION_DAMAGE);

		log("Player1 HP: %d", plyr->getHP()->getValue());
		log("Player2 HP: %d", enemy->getHP()->getValue());
		if (plyr->isDead()) {
            GameUtil::addParticles(this, plyr->getPosition(), GameUtil::ParticleType::EXPLODE);
			plyr->removeFromParent();
			GameScene2Player::player_1 = nullptr;
		}
		if (enemy->isDead()) {
            GameUtil::addParticles(this, enemy->getPosition(), GameUtil::ParticleType::EXPLODE);
			enemy->removeFromParent();
			GameScene2Player::player_2 = nullptr;
		}
	}
}

void GameScene2Player::meetPlayerWithEnemyBullet(PlayerDualSprite *plyr, EnemyBulletSprite *enemyBullet) {
	if (plyr) {
		plyr->decreaseHP(GameConfig::BULLET_DAMAGE);
		log("Player HP: %d", plyr->getHP()->getValue());
		if (plyr->isDead()) {
            GameUtil::addParticles(this, plyr->getPosition(), GameUtil::ParticleType::EXPLODE);
			plyr->removeFromParent();
			GameScene2Player::player_1 = nullptr;
		}
	}

	if (enemyBullet) {
		enemyBullet->removeFromParent();
		enemyBullet = nullptr;
        GameUtil::playEffect(GameUtil::MusicEffectType::BULLET_HIT);
	}
}

void GameScene2Player::meetEnemyWithPlayerBullet(PlayerDualSprite *enemy, PlayerBulletSprite *playerBullet) {
	if (playerBullet) {
		playerBullet->removeFromParent();
		playerBullet = nullptr;
        GameUtil::playEffect(GameUtil::MusicEffectType::BULLET_HIT);
	}

	if (enemy) {
		enemy->decreaseHP(GameConfig::BULLET_DAMAGE);
		log("Enemy HP: %d", enemy->getHP()->getValue());
		if (enemy->isDead()) {
            GameUtil::addParticles(this, enemy->getPosition(), GameUtil::ParticleType::EXPLODE);
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

void GameScene2Player::meetEnemyWithWall(PlayerDualSprite *enemy, WallSprite *wall) {
	if (enemy) {
		enemy->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
}

void GameScene2Player::meetBulletWithWall(BulletSpriteBase *bullet, WallSprite *wall) {
	if (wall && wall->isBreakable()) {
		wall->removeFromParent();
		if (bullet) {
            bullet->removeFromParent();
            GameUtil::playEffect(GameUtil::MusicEffectType::BULLET_HIT);
		}
	}
}
