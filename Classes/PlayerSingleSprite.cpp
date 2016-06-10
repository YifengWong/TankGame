#include "PlayerSingleSprite.h"
#include "GameConfig.h"
#include "PlayerBulletSprite.h"
#include "GameScene1Player.h"

USING_NS_CC;

PlayerSingleSprite::PlayerSingleSprite() {
	setHpBar();
}

PlayerSingleSprite::~PlayerSingleSprite() {
	removeHpBar();
}

PlayerSingleSprite* PlayerSingleSprite::create(GameScene1Player *scene) {
    PlayerSingleSprite *player = new (std::nothrow) PlayerSingleSprite();
    if (player && player->initWithFile("player.png")) {
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
        player->setGameScene(scene);
        player->setHP(HPValue(GameConfig::PLAYER_MAX_HP, GameConfig::PLAYER_INIT_HP));
		player->showHpBar();

        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

void PlayerSingleSprite::setMoveVal(const GameUtil::Direction &direc) {
    auto physicBody = getPhysicsBody();
    if (physicBody == nullptr) return;
    switch (direc) {
        case GameUtil::Direction::LEFT:
            physicBody->setVelocity(Vec2(-GameConfig::PLAYER_MOVE_SPEED, physicBody->getVelocity().y));
            break;
        case GameUtil::Direction::UP:
            physicBody->setVelocity(Vec2(physicBody->getVelocity().x, GameConfig::PLAYER_MOVE_SPEED));
            break;
        case GameUtil::Direction::RIGHT:
            physicBody->setVelocity(Vec2(GameConfig::PLAYER_MOVE_SPEED, physicBody->getVelocity().y));
            break;
        case GameUtil::Direction::DOWN:
            physicBody->setVelocity(Vec2(physicBody->getVelocity().x, -GameConfig::PLAYER_MOVE_SPEED));
            break;
        default:
            break;
    }
}

void PlayerSingleSprite::resetMoveVal(const GameUtil::Direction &direc) {
    auto physicBody = getPhysicsBody();
    if (physicBody == nullptr) return;
    switch (direc) {
        case GameUtil::Direction::LEFT:
            if (physicBody->getVelocity().x == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(GameConfig::PLAYER_MOVE_SPEED, 0));
            break;
        case GameUtil::Direction::UP:
            if (physicBody->getVelocity().y == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(0, -GameConfig::PLAYER_MOVE_SPEED));
            break;
        case GameUtil::Direction::RIGHT:
            if (physicBody->getVelocity().x == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(-GameConfig::PLAYER_MOVE_SPEED, 0));
            break;
        case GameUtil::Direction::DOWN:
            if (physicBody->getVelocity().y == 0) break;
            physicBody->setVelocity(physicBody->getVelocity() + Vec2(0, GameConfig::PLAYER_MOVE_SPEED));
            break;
        default:
            break;
    }
}

void PlayerSingleSprite::fire(Layer *layer, const cocos2d::Vec2 *target) {
    if (!target) return;
    auto vec = GameUtil::getUnitDirectionVector(getPosition(), *target);
    // Add bullet
    auto bullet = PlayerBulletSprite::create();
    bullet->setPosition(getPosition());
    bullet->getPhysicsBody()->setVelocity(vec * GameConfig::PLAYER_BULLET_SPEED);
    // Add to layer
    layer->addChild(bullet);
}

void PlayerSingleSprite::onRemove() {
	getGameScene()->showGameoverBtn();
}

void PlayerSingleSprite::removeHpBar() {
	hpSprite->removeFromParent();
	hpSprite = nullptr;
}

void PlayerSingleSprite::showHpBar() {
	getGameScene()->addChild(hpSprite, 1);
	schedule([&](float f) {
		updateHpBar();
	}, "HpBarUpdateSchedule");
}

void PlayerSingleSprite::updateHpBar() {
	if (hpSprite) {
		hpSprite->setPosition(this->getPosition() + cocos2d::Vec2(-7, -15));
		hpSprite->setPercentage(this->getHP()->getValue() / 10);
	}
}

void PlayerSingleSprite::setHpBar() {
	cocos2d::Sprite* sp = cocos2d::Sprite::create("hp_bar.png");

	hpSprite = cocos2d::ProgressTimer::create(sp);
	hpSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
	hpSprite->setType(cocos2d::ProgressTimerType::BAR);
	hpSprite->setBarChangeRate(cocos2d::Point(1, 0));
	hpSprite->setMidpoint(cocos2d::Point(0, 1));
	hpSprite->setPercentage(getHP()->getValue() / 10);
}