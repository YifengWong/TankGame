#include "PlayerDualSprite.h"
#include "GameConfig.h"
#include "PlayerBulletSprite.h"
#include "EnemyBulletSprite.h"

USING_NS_CC;

PlayerDualSprite* PlayerDualSprite::create(PlayerDualSprite::VSPlayerType type) {
	PlayerDualSprite *player = new (std::nothrow) PlayerDualSprite();
	player->dir = Direction::UP;
	player->type = type;
	if (player) {
		if (type == PlayerDualSprite::PLAYER_1 && player->initWithFile("player.png")) {
			player->autorelease();

			// Create physics body
			auto physicBody = PhysicsBody::createBox(player->getContentSize());
			// Set group and bitmasks
			physicBody->setGroup(GameConfig::PLAYER_PHYSIC_GROUP);
			physicBody->setCategoryBitmask(GameConfig::PLAYER_PHYSIC_CATEGORY_BM);
			physicBody->setCollisionBitmask(GameConfig::PLAYER_PHYSIC_COLLISION_BM);
			physicBody->setContactTestBitmask(GameConfig::PLAYER_PHYSIC_CONTACT_BM);
			physicBody->setRotationEnable(false);
			physicBody->setTag(GameConfig::PLAYER_TAG);

			// Set player sprites
			player->setAnchorPoint(Vec2(0.5, 0.5));
			player->setPhysicsBody(physicBody);
            player->setHP(HPValue(GameConfig::PLAYER_MAX_HP, GameConfig::PLAYER_INIT_HP));


		} else if (type == PlayerDualSprite::PLAYER_2 && player->initWithFile("enemy.png")) {
			player->autorelease();

			// Create physics body
			auto physicBody = PhysicsBody::createBox(player->getContentSize());
			// Set group and bitmasks
			physicBody->setGroup(GameConfig::ENEMY_PHYSIC_GROUP);
			physicBody->setCategoryBitmask(GameConfig::ENEMY_PHYSIC_CATEGORY_BM);
			physicBody->setCollisionBitmask(GameConfig::ENEMY_PHYSIC_COLLISION_BM);
			physicBody->setContactTestBitmask(GameConfig::ENEMY_PHYSIC_CONTACT_BM);
			physicBody->setRotationEnable(false);
			physicBody->setTag(GameConfig::ENEMY_TAG);

			// Set player sprites
			player->setAnchorPoint(Vec2(0.5, 0.5));
			player->setPhysicsBody(physicBody);
            player->setHP(HPValue(GameConfig::PLAYER_MAX_HP, GameConfig::PLAYER_INIT_HP));

		}

		return player;
	}

	CC_SAFE_DELETE(player);
	return nullptr;
}

void PlayerDualSprite::setMoveVal(const Direction &direc) {
	auto physicBody = getPhysicsBody();
	if (physicBody == nullptr) return;

	dir = direc;
	switch (direc) {
	case LEFT:
		setRotation(270);
		physicBody->setVelocity(Vec2(-GameConfig::PLAYER_MOVE_SPEED, physicBody->getVelocity().y));
		break;
	case UP:
		setRotation(0);
		physicBody->setVelocity(Vec2(physicBody->getVelocity().x, GameConfig::PLAYER_MOVE_SPEED));
		break;
	case RIGHT:
		setRotation(90);
		physicBody->setVelocity(Vec2(GameConfig::PLAYER_MOVE_SPEED, physicBody->getVelocity().y));
		break;
	case DOWN:
		setRotation(180);
		physicBody->setVelocity(Vec2(physicBody->getVelocity().x, -GameConfig::PLAYER_MOVE_SPEED));
		break;
	default:
		break;
	}
}

void PlayerDualSprite::resetMoveVal(const Direction &direc) {
	auto physicBody = getPhysicsBody();
	if (physicBody == nullptr) return;
	switch (direc) {
	case LEFT:
		if (physicBody->getVelocity().x == 0) break;
		physicBody->setVelocity(physicBody->getVelocity() + Vec2(GameConfig::PLAYER_MOVE_SPEED, 0));
		break;
	case UP:
		if (physicBody->getVelocity().y == 0) break;
		physicBody->setVelocity(physicBody->getVelocity() + Vec2(0, -GameConfig::PLAYER_MOVE_SPEED));
		break;
	case RIGHT:
		if (physicBody->getVelocity().x == 0) break;
		physicBody->setVelocity(physicBody->getVelocity() + Vec2(-GameConfig::PLAYER_MOVE_SPEED, 0));
		break;
	case DOWN:
		if (physicBody->getVelocity().y == 0) break;
		physicBody->setVelocity(physicBody->getVelocity() + Vec2(0, GameConfig::PLAYER_MOVE_SPEED));
		break;
	default:
		break;
	}
}

void PlayerDualSprite::fire(Layer *layer, const cocos2d::Vec2 *target) {
	Sprite* bullet;
	if (type == PlayerDualSprite::PLAYER_1) bullet = PlayerBulletSprite::create();
	else bullet = EnemyBulletSprite::create();

	Vec2 vec;
	if (dir == LEFT) vec.y = 0, vec.x = -1;
	else if (dir == RIGHT) vec.y = 0, vec.x = 1;
	else if (dir == UP) vec.y = 1, vec.x = 0;
	else if (dir == DOWN) vec.y = -1, vec.x = 0;

	// Add bullet
	bullet->setPosition(getPosition());
	bullet->getPhysicsBody()->setVelocity(vec * GameConfig::PLAYER_BULLET_SPEED);
	// Add to layer
	layer->addChild(bullet);
}