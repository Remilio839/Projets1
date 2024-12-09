#include "Enemy.h"

USING_NS_CC;

Enemy* Enemy::create()
{
    Enemy* ret = new (std::nothrow) Enemy();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Enemy::init()
{
    if (!Node::init())
        return false;

    health = 1000;
    maxHealth = 1000;

    sprite = Sprite::create("enemy.png");
    sprite->setScale(0.2f);
    this->addChild(sprite, 0);

    healthLabel = Label::createWithSystemFont("Enemy Health: 1000", "Arial", 24);
    healthLabel->setPosition(Vec2(0, sprite->getContentSize().height + 20));
    healthLabel->setColor(Color3B::WHITE);
    this->addChild(healthLabel, 1);

    return true;
}

void Enemy::setHealth(int value)
{
    health = value;
    if (health < 0)
        health = 0;

    healthLabel->setString("Enemy Health: " + std::to_string(health));

    if (health <= 0) {
        CCLOG("Enemy defeated!");
    }
}

void Enemy::shootAtPlayer(const Vec2& targetPosition)
{
    auto fireball = Sprite::create("fireball.png");
    fireball->setScale(0.05f);
    fireball->setPosition(this->getPosition());
    this->getParent()->addChild(fireball, 2);

    auto physicsBody = PhysicsBody::createCircle(fireball->getContentSize().width * 0.05f);

    Vec2 direction = targetPosition - this->getPosition();
    direction.normalize();

    int randomSpeed = rand() % 400 + 700;

    direction = direction * randomSpeed;

    physicsBody->setVelocity(direction);
    physicsBody->setGravityEnable(true);
    physicsBody->setContactTestBitmask(true);

    fireball->setPhysicsBody(physicsBody);
}
